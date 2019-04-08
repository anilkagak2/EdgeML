# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT license.

import argparse
import datetime
from distutils.dir_util import copy_tree
import os
import shutil
import operator
import tempfile
import traceback

from edgeml.tools.seedot.converter.converter import Converter

import edgeml.tools.seedot.common as Common
from edgeml.tools.seedot.compiler import Compiler
from edgeml.tools.seedot.predictor import Predictor
import edgeml.tools.seedot.util as Util


class Main:

    def __init__(self, algo, version, target, trainingFile, testingFile, modelDir, sf, workers):
        self.algo, self.version, self.target, self.trainingFile, self.testingFile, self.modelDir, self.sf, self.numWorkers = algo, version, target, trainingFile, testingFile, modelDir, sf, workers
        self.accuracy = {}

    def setup(self):
        curr_dir = os.path.dirname(os.path.realpath(__file__))
        
        copy_tree(os.path.join(curr_dir, "Predictor"), Common.tempdir)

        for fileName in ["arduino.ino", "config.h", "library.h", "predict.h"]:
            srcFile = os.path.join(curr_dir, "arduino", fileName)
            destFile = os.path.join(Common.outdir, fileName)
            shutil.copyfile(srcFile, destFile)

    # Generate the fixed-point code using the input generated from the
    # Converter project
    def compile(self, target, sf):
        print("Generating code...", end='')

        # Set input and output files
        inputFile = os.path.join(Common.tempdir, "input.sd")
        profileLogFile = os.path.join(
            Common.tempdir, "output", self.algo + "-float", "profile.txt")

        if target == Common.Target.Arduino:
            outputFile = os.path.join(Common.outdir, "predict.cpp")
        elif target == Common.Target.X86:
            outputFile = os.path.join(Common.tempdir, "seedot_fixed.cpp")

        try:
            obj = Compiler(self.algo, target, inputFile,
                           outputFile, profileLogFile, sf, self.numWorkers)
            obj.run()
        except:
            print("failed!\n")
            traceback.print_exc()
            return False

        print("completed")
        return True

    # Run the converter project to generate the input files using reading the
    # training model
    def convert(self, version, datasetType, target):
        print("Generating input files for %s %s dataset..." %
              (version, datasetType), end='')

        # Create output dirs
        if target == Common.Target.Arduino:
            outputDir = os.path.join(Common.outdir, "input")
            datasetOutputDir = outputDir
        elif target == Common.Target.X86:
            outputDir = Common.tempdir
            datasetOutputDir = os.path.join(Common.tempdir, "input")
        else:
            assert False

        os.makedirs(datasetOutputDir, exist_ok=True)
        os.makedirs(outputDir, exist_ok=True)

        try:
            obj = Converter(self.algo, version, datasetType, target,
                            datasetOutputDir, outputDir, self.numWorkers)
            obj.setInput(self.modelDir, self.trainingFile, self.testingFile)
            obj.run()
        except Exception as e:
            traceback.print_exc()
            return False

        print("done\n")
        return True

    # Build and run the Predictor project
    def predict(self, version, datasetType):
        outputDir = os.path.join(
            Common.tempdir, "output", self.algo + "-" + version)

        curDir = os.getcwd()
        os.chdir(Common.tempdir)

        obj = Predictor(self.algo, version, datasetType, outputDir)
        acc = obj.run()

        os.chdir(curDir)

        return acc

    # Compile and run the generated code once for a given scaling factor
    def runOnce(self, version, datasetType, target, sf):
        res = self.compile(target, sf)
        if res == False:
            return False, False

        acc = self.predict(version, datasetType)
        if acc == None:
            return False, True

        self.accuracy[sf] = acc
        print("Accuracy is %.3f%%\n" % (acc))

        return True, False

    # Iterate over multiple scaling factors and store their accuracies
    def performSearch(self):
        start, end = Common.maxScaleRange
        searching = False

        for i in range(start, end, -1):
            print("Testing with max scale factor of " + str(i))

            res, exit = self.runOnce(
                Common.Version.Fixed, Common.DatasetType.Training, Common.Target.X86, i)

            if exit == True:
                return False

            # The iterator logic is as follows:
            # Search begins when the first valid scaling factor is found (runOnce returns True)
            # Search ends when the execution fails on a particular scaling factor (runOnce returns False)
            # This is the window where valid scaling factors exist and we
            # select the one with the best accuracy
            if res == True:
                searching = True
            elif searching == True:
                break

        # If search didn't begin at all, something went wrong
        if searching == False:
            return False

        print("\nSearch completed\n")
        print("----------------------------------------------")
        print("Best performing scaling factors with accuracy:")

        self.sf = self.getBestScale()

        return True

    # Reverse sort the accuracies, print the top 5 accuracies and return the
    # best scaling factor
    def getBestScale(self):
        sorted_accuracy = dict(
            sorted(self.accuracy.items(), key=operator.itemgetter(1), reverse=True)[:5])
        print(sorted_accuracy)
        return next(iter(sorted_accuracy))

    # Find the scaling factor which works best on the training dataset and
    # predict on the testing dataset
    def findBestScalingFactor(self):
        print("-------------------------------------------------")
        print("Performing search to find the best scaling factor")
        print("-------------------------------------------------\n")

        # Generate input files for training dataset
        res = self.convert(Common.Version.Fixed,
                           Common.DatasetType.Training, Common.Target.X86)
        if res == False:
            return False

        # Search for the best scaling factor
        res = self.performSearch()
        if res == False:
            return False

        print("Best scaling factor = %d" % (self.sf))

        return True

    def runOnTestingDataset(self):
        print("\n-------------------------------")
        print("Prediction on testing dataset")
        print("-------------------------------\n")

        print("Setting max scaling factor to %d\n" % (self.sf))

        # Generate files for the testing dataset
        res = self.convert(Common.Version.Fixed,
                           Common.DatasetType.Testing, Common.Target.X86)
        if res == False:
            return False

        # Compile and run code using the best scaling factor
        res = self.runOnce(
            Common.Version.Fixed, Common.DatasetType.Testing, Common.Target.X86, self.sf)
        if res == False:
            return False

        return True

    # Generate files for training dataset and perform a profiled execution
    def collectProfileData(self):
        print("-----------------------")
        print("Collecting profile data")
        print("-----------------------")

        res = self.convert(Common.Version.Float,
                           Common.DatasetType.Training, Common.Target.X86)
        if res == False:
            return False

        acc = self.predict(Common.Version.Float, Common.DatasetType.Training)
        if acc == None:
            return False

        print("Accuracy is %.3f%%\n" % (acc))

    # Generate code for Arduino
    def compileForTarget(self):
        print("------------------------------")
        print("Generating code for %s..." % (self.target))
        print("------------------------------\n")

        res = self.convert(Common.Version.Fixed,
                           Common.DatasetType.Testing, self.target)
        if res == False:
            return False

        # Copy file
        srcFile = os.path.join(Common.outdir, "input", "seedot_fixed_model.h")
        destFile = os.path.join(Common.outdir, "model.h")
        shutil.copyfile(srcFile, destFile)

        res = self.compile(self.target, self.sf)
        if res == False:
            return False

    def runForFixed(self):
        # Collect runtime profile for ProtoNN
        if self.algo == Common.Algo.Protonn:
            res = self.collectProfileData()
            if res == False:
                return False

        # Obtain best scaling factor
        if self.sf == None:
            res = self.findBestScalingFactor()
            if res == False:
                return False

        res = self.runOnTestingDataset()
        if res == False:
            return False
        else:
            self.testingAccuracy = self.accuracy[self.sf]

        # Generate code for target
        self.compileForTarget()

        return True

    def runForFloat(self):
        print("---------------------------")
        print("Executing for X86 target...")
        print("---------------------------\n")

        res = self.convert(Common.Version.Float,
                           Common.DatasetType.Testing, Common.Target.X86)
        if res == False:
            return False

        acc = self.predict(Common.Version.Float, Common.DatasetType.Testing)
        if acc == None:
            return False
        else:
            self.testingAccuracy = acc

        print("Accuracy is %.3f%%\n" % (acc))

        print("------------------------------")
        print("Generating code for Arduino...")
        print("------------------------------\n")

        res = self.convert(Common.Version.Float,
                           Common.DatasetType.Testing, Common.Target.Arduino)
        if res == False:
            return False

        curr_dir = os.path.dirname(os.path.realpath(__file__))

        # Copy model.h
        srcFile = os.path.join(curr_dir, Common.outdir, "input",
                               self.algo + "_" + "float_model.h")
        destFile = os.path.join(Common.outdir, "model.h")
        shutil.copyfile(srcFile, destFile)

        # Copy predict.cpp
        srcFile = os.path.join(
            curr_dir, "arduino", "floating-point", self.algo + "_float.cpp")
        destFile = os.path.join(Common.outdir, "predict.cpp")
        shutil.copyfile(srcFile, destFile)

        return True

    def run(self):

        self.setup()

        if self.version == Common.Version.Fixed:
            return self.runForFixed()
        else:
            return self.runForFloat()
