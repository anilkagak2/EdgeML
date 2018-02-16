#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Windows.h>

typedef int16_t MYINT;

#include "protonn.h"
#include "bonsai.h"
#include "profile.h"

using namespace std;

enum Algo { Bonsai, Protonn };
enum Version { Fixed, Float };
enum DatasetType { Training, Testing };

vector<float> readCSVLine(string line) {
	vector<float> tokens;

	stringstream stream(line);
	string str;

	while (getline(stream, str, ','))
		tokens.push_back((float)atof(str.c_str()));

	return tokens;
}

vector<float> getFeatures(string line) {
	static int featuresLength = -1;

	vector<float> features = readCSVLine(line);

	if (featuresLength == -1)
		featuresLength = (int)features.size();

	if (features.size() != featuresLength)
		throw "Number of row entries in X is inconsistent";

	return features;
}

int getLabel(string line) {
	static int labelLength = -1;

	vector<float> labels = readCSVLine(line);

	if (labelLength == -1)
		labelLength = (int)labels.size();

	if (labels.size() != labelLength || labels.size() != 1)
		throw "Number of row entries in Y is inconsistent";

	return (int)labels.front();
}

void createDir(string dir) {
	bool result = CreateDirectory(dir.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
	if (result == false)
		throw "Creating output directory failed!";

	return;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		cout << "No arguments supplied" << endl;
		return 1;
	}

	Algo algo;
	if (strcmp(argv[1], "bonsai") == 0)
		algo = Bonsai;
	else if (strcmp(argv[1], "protonn") == 0)
		algo = Protonn;
	else {
		cout << "Argument mismatch for algo\n";
		return 1;
	}
	string algoStr = argv[1];

	Version version;
	if (strcmp(argv[2], "fixed") == 0)
		version = Fixed;
	else if (strcmp(argv[2], "float") == 0)
		version = Float;
	else {
		cout << "Argument mismatch for version\n";
		return 1;
	}
	string versionStr = argv[2];

	DatasetType datasetType;
	if (strcmp(argv[3], "training") == 0)
		datasetType = Training;
	else if (strcmp(argv[3], "testing") == 0)
		datasetType = Testing;
	else {
		cout << "Argument mismatch for dataset type\n";
		return 1;
	}
	string datasetTypeStr = argv[3];

	string inputDir = algoStr + "\\" + versionStr + "-" + datasetTypeStr + "\\";

	ifstream featuresFile(inputDir + "X.csv");
	ifstream lablesFile(inputDir + "Y.csv");

	if (featuresFile.good() == false || lablesFile.good() == false)
		throw "Input files doesn't exist";

	string outputDir = "output\\" + algoStr + "-" + versionStr;
	createDir(outputDir);

	string outputFile = outputDir + "\\prediction-info-" + datasetTypeStr + ".txt";
	string statsFile = outputDir + "\\stats-" + datasetTypeStr + ".txt";

	ofstream output(outputFile);
	ofstream stats(statsFile);

	int correct = 0, total = 0;

	bool alloc = false;
	MYINT **features_int = NULL, features_size = -1;

	initializeRange();

	int limit = -1;

	string line1, line2;
	while (getline(featuresFile, line1) && getline(lablesFile, line2)) {

		if (limit != -1)
			if (total >= limit)
				break;

		vector<float> features = getFeatures(line1);
		int label = getLabel(line2);

		if (version == Fixed) {
			if (alloc == false) {
				features_size = (int)features.size();
				features_int = new MYINT*[features_size];
				for (int i = 0; i < features_size; i++)
					features_int[i] = new MYINT[1];
				alloc = true;
			}

			for (int i = 0; i < features_size; i++)
				features_int[i][0] = (MYINT)features.at(i);
		}

		int res;
		if (algo == Bonsai && version == Fixed)
			res = bonsaiFixed(features_int);
		else if (algo == Bonsai && version == Float)
			res = bonsaiFloat(&features[0]);
		else if (algo == Protonn && version == Fixed)
			res = protonnFixed(features_int);
		else if (algo == Protonn && version == Float)
			res = protonnFloat(&features[0]);

		if ((res + 1) == label)
			correct++;
		else
			output << "Incorrect prediction for input " << total + 1 << endl;

		total++;
	}

	if (version == Fixed) {
		for (int i = 0; i < features_size; i++)
			delete features_int[i];
		delete features_int;
	}

	float accuracy = (float)correct / total * 100.0f;

	cout.precision(3);
	cout << fixed;
	cout << "\n\n#test points = " << total << endl;
	cout << "Correct predictions = " << correct << endl;
	cout << "Accuracy = " << accuracy << "\n\n";

	output.precision(3);
	output << fixed;
	output << "\n\n#test points = " << total << endl;
	output << "Correct predictions = " << correct << endl;
	output << "Accuracy = " << accuracy << "\n\n";
	output.close();

	stats.precision(3);
	stats << fixed;
	stats << accuracy << "\n";
	stats.close();

	if (datasetType == Training)
		dumpRange(outputDir + "\\profile.txt");

	return 0;
}
