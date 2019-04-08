#pragma once

#define P_SPARSE_W 1
#define P_NORM 1

namespace protonn_float {

const int D = 256;
const int d = 10;
const int p = 26;
const int c = 2;
const float g2 = 0.011863f;

const float norm[10] = {
	-0.001229f, -0.002218f, -0.009835f, -0.003974f, -0.002963f, 0.000189f, 0.000952f, -0.003074f, -0.007580f, 0.003904f, 
};

const float Wval[516] = {
	0.774957f, -0.737940f, -1.340837f, 0.741553f, 0.657024f, 0.424531f, -1.059115f, 0.823317f, -0.108933f, -0.096977f, -0.079217f, 0.636943f, 0.239933f, -0.275558f, -0.623687f, -0.990260f, 0.702781f, 0.178246f, 0.344746f, -0.776143f, 0.752061f, -0.545383f, 0.429313f, -0.133985f, -0.148498f, -0.418214f, 0.421971f, -0.651596f, -1.932824f, 0.735615f, 1.427408f, 0.847559f, 0.392831f, -0.653682f, 0.271342f, 0.144613f, 0.254517f, -0.093024f, -0.141831f, -1.004837f, 0.041762f, -1.135483f, 0.623877f, 0.206448f, -0.011439f, -0.104586f, -0.485498f, 0.363253f, 0.910090f, -0.007558f, 0.321773f, 1.288784f, 1.435198f, 0.658889f, 0.206723f, -0.779890f, -0.665278f, -0.003344f, -0.611956f, -1.021516f, 0.748199f, 0.967719f, -0.266870f, 0.545723f, -0.625378f, -0.501556f, -0.001853f, 1.041801f, 0.543792f, 0.407323f, 0.797935f, -0.594615f, 0.650413f, -0.837987f, -0.783397f, 0.157963f, -0.513267f, -0.234490f, -0.417403f, 0.118771f, -0.448331f, -0.454993f, 0.636128f, -0.457300f, -0.551281f, 0.211592f, 0.480213f, 0.151203f, -0.241881f, 0.511401f, 0.015453f, -0.144543f, 0.781501f, -0.186517f, -0.436308f, -0.574902f, 0.233877f, -0.190972f, 0.228942f, -0.119976f, -0.222858f, 0.265482f, -0.379174f, 0.111839f, -0.063312f, -0.595279f, -1.039103f, 0.749880f, -0.325123f, 0.361565f, -0.175979f, -0.773557f, -0.185832f, 0.151872f, 0.418293f, 0.054887f, 0.758869f, 0.070477f, 0.273568f, -0.266221f, 0.139607f, 0.204255f, 0.766783f, 0.802446f, 0.164590f, 0.399402f, -0.854062f, 0.158034f, -1.040775f, -0.065949f, -0.724032f, 0.435866f, -0.715373f, -0.361511f, 0.348023f, -0.412460f, -0.002313f, 0.128462f, 0.370071f, 0.739675f, 0.232932f, -0.377351f, 0.101635f, 0.296126f, 0.156516f, -0.613812f, -0.985523f, -0.014312f, 0.546803f, -0.282346f, -0.676678f, 0.233436f, -0.199709f, 0.114693f, 0.109016f, 0.294032f, 0.369685f, -0.171487f, 0.553357f, -1.092076f, 0.455097f, -1.820420f, -0.491742f, -0.792661f, -1.088519f, 0.865048f, 0.808319f, -0.699714f, 0.589623f, 1.121099f, 0.668104f, 0.607009f, 0.495048f, 0.944682f, -1.260840f, -0.411897f, 0.166408f, -0.002868f, -0.722271f, 0.193537f, 0.070608f, 0.573942f, 0.966478f, -0.139317f, 0.257970f, -0.253297f, 0.243062f, -0.324854f, 0.411479f, -1.201601f, 0.074534f, 0.751551f, -1.218999f, 0.433890f, 0.188666f, -0.840055f, 0.251960f, -0.681401f, 0.270301f, 0.820755f, -0.535763f, -0.050104f, 0.533937f, -0.545248f, -0.328416f, -1.319030f, -0.289372f, -0.449770f, -1.392196f, 1.063982f, 0.326756f, 0.259650f, 0.342184f, -0.377450f, 0.487664f, 0.079738f, 0.553407f, 0.591911f, 0.354165f, -0.320680f, -0.086178f, 0.239730f, 0.276463f, -0.690316f, -1.165668f, -0.453264f, 0.038175f, -0.484408f, -0.399084f, -0.411529f, 0.335309f, 0.147687f, -0.546338f, 0.424529f, -0.421988f, 0.042848f, -0.179821f, -0.376801f, -0.256103f, -0.327414f, 1.221656f, -0.336323f, -0.056391f, -0.953927f, -0.308257f, -0.724982f, -0.194416f, -0.701981f, -1.087389f, 0.571696f, -0.729030f, -1.330347f, 0.560065f, -0.723278f, -0.600656f, -0.353012f, -0.338919f, -0.265706f, 0.304749f, -0.577579f, -0.346982f, -0.068996f, 0.412084f, -0.441946f, -0.558444f, 0.458091f, -0.084416f, -0.225775f, 0.313120f, -0.743752f, 0.271542f, -1.272366f, 0.309816f, -0.057918f, -0.293195f, -0.551386f, -0.783747f, 0.224705f, -0.229022f, 0.033284f, 0.286304f, -0.060206f, 1.075543f, -0.354711f, -0.957499f, -0.902011f, -0.676603f, -0.574632f, -0.726228f, 0.657259f, 0.820130f, 0.052298f, -0.191624f, -0.640570f, 0.244463f, -0.105317f, 0.138644f, -1.244617f, 0.109860f, 0.173901f, -0.348284f, -1.027029f, 0.116188f, -0.717394f, 0.320284f, -0.277686f, 0.579485f, 0.266363f, 0.233114f, -0.484478f, 0.310202f, -0.478081f, -0.647064f, 0.396815f, 0.954123f, 0.548833f, 0.124427f, 0.641242f, 0.698905f, -0.586224f, 0.541871f, -0.837754f, -0.501356f, -0.245272f, -0.160741f, 0.349153f, -0.259879f, -0.960655f, 0.273176f, 0.024254f, -0.653317f, -0.017230f, 0.586738f, -0.209576f, -0.320318f, -0.039344f, 0.130281f, -0.257569f, -0.150494f, -0.673972f, -0.163553f, 0.364951f, -0.224212f, -1.201323f, -0.149173f, -0.991321f, 0.662676f, -0.671086f, -0.298299f, -0.591771f, 0.502431f, -0.496996f, 0.447061f, 0.440949f, 0.637199f, -0.352862f, -0.347299f, -0.424940f, 0.272359f, 0.080480f, 0.513812f, -0.300193f, 0.227964f, -0.289424f, -0.571041f, 0.522671f, 0.182746f, 0.597204f, -0.160842f, 0.800155f, -0.323847f, 0.561021f, -0.482582f, 0.695423f, -0.393253f, -0.035838f, -0.654277f, -0.193610f, -0.024902f, -0.340005f, -0.975938f, 0.224903f, -1.753717f, 0.628964f, 0.946878f, -0.796338f, 0.302721f, -0.291239f, 0.426886f, 0.191245f, 0.170867f, 0.259296f, -0.007319f, -0.031455f, 0.497812f, -0.046072f, -0.363236f, 0.276762f, -0.287800f, 0.327655f, -0.948349f, 0.836288f, 0.003299f, 0.119725f, 0.432021f, -0.397807f, 0.993195f, -0.661684f, -0.032157f, -0.230916f, -0.768273f, 0.720451f, -0.263103f, 0.330980f, -0.386860f, -0.535208f, -0.249115f, 0.062860f, -0.442532f, -0.013667f, -0.155125f, 0.265545f, 0.681386f, 0.674037f, 0.094703f, 0.191143f, 0.131434f, 0.449379f, -0.061807f, -0.235330f, 0.162997f, -0.818879f, 0.431626f, -0.013879f, -0.241255f, -0.504727f, -0.131869f, 0.952666f, -0.345507f, -0.236683f, -0.726076f, -0.709846f, -0.871396f, -0.921261f, 0.116384f, 0.130785f, -0.071293f, 0.422548f, 0.121049f, 1.402446f, -0.555743f, 0.443364f, 0.061916f, -0.051612f, 0.057981f, 0.499406f, 1.073347f, 0.815118f, 0.236036f, 0.020260f, -1.028034f, 0.006837f, 0.463959f, 0.185052f, -0.579665f, 0.634132f, -1.300445f, 0.386499f, -0.004220f, 1.285553f, 0.534152f, 0.413936f, 0.746953f, -1.013132f, 0.408783f, -1.380450f, -0.963887f, 0.712046f, 0.618952f, -1.208456f, -0.641317f, -1.655570f, 0.664160f, -0.634082f, 0.510080f, -0.526548f, -0.765668f, 0.957934f, 0.267475f, 0.543827f, -0.382703f, 0.119663f, 0.331849f, 0.755013f, -0.077510f, -0.533202f, 0.043368f, -0.607534f, -0.348541f, -0.659595f, -0.683847f, 0.048150f, 0.037745f, -0.337676f, -0.378943f, 0.153862f, -0.504327f, 0.782551f, 0.797019f, 0.855468f, 0.644597f, 0.607904f, -0.688119f, 0.945623f, 1.371671f, -0.888265f, 
};

const MYINT Widx[772] = {
	2, 3, 10, 0, 5, 0, 3, 9, 0, 8, 10, 0, 9, 0, 5, 9, 10, 0, 0, 1, 2, 8, 9, 10, 0, 2, 6, 0, 8, 10, 0, 3, 4, 0, 8, 0, 4, 10, 0, 0, 2, 4, 0, 2, 6, 0, 6, 0, 1, 0, 2, 10, 0, 5, 9, 10, 0, 2, 4, 0, 7, 0, 2, 3, 6, 0, 1, 2, 7, 8, 10, 0, 2, 4, 7, 10, 0, 1, 2, 10, 0, 6, 7, 10, 0, 2, 3, 7, 0, 1, 9, 0, 1, 2, 5, 8, 0, 4, 8, 9, 0, 10, 0, 3, 5, 6, 9, 0, 5, 0, 2, 0, 2, 3, 6, 8, 0, 6, 10, 0, 7, 0, 3, 7, 10, 0, 3, 5, 6, 7, 8, 0, 5, 7, 0, 2, 5, 7, 0, 9, 0, 2, 9, 0, 1, 2, 7, 0, 2, 8, 0, 0, 4, 0, 7, 10, 0, 4, 10, 0, 4, 5, 6, 0, 3, 4, 0, 8, 0, 1, 10, 0, 4, 10, 0, 5, 7, 10, 0, 10, 0, 1, 2, 3, 4, 8, 9, 0, 3, 6, 8, 0, 1, 9, 0, 5, 0, 3, 0, 1, 5, 0, 4, 0, 3, 4, 0, 9, 0, 9, 0, 7, 0, 5, 8, 0, 10, 0, 1, 2, 3, 5, 6, 10, 0, 5, 7, 8, 0, 1, 3, 0, 4, 0, 2, 7, 9, 0, 8, 0, 8, 0, 3, 0, 10, 0, 2, 0, 3, 4, 0, 5, 0, 4, 9, 0, 7, 0, 3, 0, 2, 4, 7, 10, 0, 7, 8, 0, 4, 0, 3, 0, 8, 0, 8, 9, 10, 0, 8, 0, 2, 7, 0, 3, 6, 7, 0, 1, 0, 0, 5, 6, 0, 6, 0, 8, 0, 8, 0, 9, 0, 2, 8, 0, 1, 4, 10, 0, 5, 9, 0, 1, 2, 3, 10, 0, 4, 6, 0, 2, 10, 0, 1, 2, 3, 0, 1, 3, 4, 8, 0, 2, 0, 0, 9, 0, 1, 2, 5, 0, 0, 2, 0, 2, 6, 8, 9, 0, 3, 0, 1, 4, 0, 3, 8, 0, 5, 8, 0, 6, 8, 0, 2, 0, 1, 4, 6, 0, 2, 0, 9, 0, 2, 10, 0, 10, 0, 3, 9, 0, 1, 4, 7, 0, 3, 0, 9, 0, 1, 3, 4, 10, 0, 3, 9, 0, 3, 0, 2, 8, 0, 3, 4, 10, 0, 2, 4, 5, 0, 9, 0, 5, 10, 0, 1, 0, 6, 0, 2, 3, 4, 6, 9, 0, 2, 6, 0, 8, 0, 3, 4, 6, 8, 0, 2, 3, 0, 0, 5, 8, 0, 7, 9, 10, 0, 7, 0, 0, 5, 10, 0, 2, 10, 0, 2, 3, 4, 8, 10, 0, 8, 9, 10, 0, 1, 0, 2, 0, 0, 1, 5, 9, 0, 3, 8, 0, 1, 5, 6, 10, 0, 1, 5, 0, 1, 0, 3, 4, 7, 9, 0, 3, 0, 4, 5, 7, 0, 0, 1, 7, 10, 0, 2, 10, 0, 3, 5, 0, 2, 0, 0, 0, 1, 0, 6, 0, 3, 6, 0, 1, 10, 0, 1, 9, 0, 3, 8, 10, 0, 3, 0, 10, 0, 5, 9, 10, 0, 1, 4, 5, 8, 0, 1, 8, 0, 0, 2, 9, 0, 1, 9, 0, 2, 5, 7, 0, 1, 2, 0, 1, 8, 0, 1, 7, 9, 0, 0, 0, 0, 2, 3, 0, 5, 0, 4, 7, 9, 0, 1, 3, 5, 7, 10, 0, 6, 9, 0, 3, 8, 10, 0, 10, 0, 5, 10, 0, 2, 10, 0, 2, 5, 6, 7, 9, 0, 2, 8, 0, 3, 5, 0, 1, 0, 3, 4, 7, 9, 0, 1, 3, 8, 0, 7, 0, 6, 7, 0, 4, 0, 7, 10, 0, 6, 8, 0, 6, 0, 1, 2, 0, 1, 3, 6, 8, 9, 0, 1, 2, 3, 7, 10, 0, 4, 0, 8, 0, 5, 8, 0, 0, 3, 0, 7, 9, 0, 4, 0, 1, 7, 0, 1, 2, 8, 10, 0, 5, 7, 0, 4, 6, 7, 0, 1, 2, 4, 7, 10, 0, 1, 2, 9, 10, 0, 1, 2, 6, 7, 0, 3, 8, 10, 0, 7, 0, 6, 8, 0, 2, 3, 5, 0, 1, 10, 0, 2, 0, 0, 1, 6, 7, 0, 5, 7, 0, 2, 4, 5, 9, 0, 8, 0, 1, 2, 5, 0, 3, 5, 0, 0, 2, 8, 10, 0, 4, 8, 10, 0, 6, 9, 10, 0, 5, 0, 3, 5, 9, 0, 0, 3, 6, 8, 0, 5, 10, 0, 5, 6, 7, 0, 2, 7, 0, 
};

const float B[10][26] = {
	-3.447390f, 7.270600f, 0.451219f, -0.446814f, 6.982720f, 4.071000f, 3.709550f, -0.705726f, -7.512320f, 2.240710f, 7.475420f, -3.851410f, 3.411920f, 5.802970f, 8.275460f, 9.844730f, 8.139910f, -2.631180f, 4.786210f, 4.846340f, 9.719940f, 5.976020f, 2.406440f, 2.814930f, -6.724940f, 6.145180f, 
	11.370900f, 3.611570f, 1.700900f, 14.031700f, -3.867370f, -7.968640f, -3.829360f, 10.822800f, -2.461530f, 1.078140f, 5.714750f, 4.719600f, -2.604630f, -4.922500f, 2.776300f, -2.748700f, -1.429370f, 2.961080f, -0.356387f, -0.828819f, -4.267970f, -2.493760f, -3.214610f, -2.802980f, 6.013460f, 5.744230f, 
	-10.204400f, -5.498620f, -4.033080f, -24.235900f, -5.033810f, -9.135900f, 3.692420f, -13.062500f, -3.375760f, -15.413500f, -22.430200f, -10.113000f, -12.950200f, -8.058410f, -16.409100f, -0.546094f, -19.306800f, -8.087020f, -23.729400f, -1.605010f, -13.282100f, -7.549990f, -14.020000f, -10.238900f, -12.962100f, -3.820880f, 
	-0.041425f, 0.228992f, -2.983450f, -2.710030f, 0.207108f, -2.960090f, 0.203372f, 2.752600f, -2.466100f, -5.994880f, -4.647810f, -4.194710f, -3.893730f, 1.022430f, -4.765450f, -3.449450f, -1.552480f, -2.951220f, -2.236270f, -0.467903f, -2.584660f, 3.048160f, -3.267410f, -2.222260f, -3.754400f, -0.392210f, 
	-2.141260f, -0.569464f, -4.582970f, -5.524560f, -7.116210f, -7.214490f, -7.744800f, 0.090926f, -3.281370f, -4.329660f, 4.175380f, -0.190327f, 4.043870f, -5.751280f, 4.044770f, -11.299200f, -6.931930f, -4.427790f, -6.471980f, 1.755630f, -6.952340f, 1.727660f, -10.829400f, -3.082110f, -3.029570f, 4.960580f, 
	-0.783665f, -3.144350f, 2.922120f, -1.127830f, 3.717130f, -1.324730f, -3.654750f, -0.559077f, 2.698710f, 2.837470f, -3.041860f, -2.318350f, 3.726260f, 2.728030f, 0.460749f, 2.474870f, -2.825850f, 0.786466f, -0.118838f, 2.784830f, -0.689486f, -2.955170f, 0.366459f, -0.122022f, -1.923550f, 0.405512f, 
	3.258380f, 1.986190f, 4.336730f, 5.908610f, 8.948130f, -1.175760f, 0.311655f, 8.101850f, 2.809520f, -1.619970f, 3.347840f, -3.440840f, 7.514980f, -0.766793f, 12.283600f, -4.104110f, 6.423610f, 6.719260f, 10.769300f, -5.325920f, -1.670020f, 10.004900f, 5.486470f, 1.724750f, 15.005200f, 9.993380f, 
	-10.373900f, -6.687950f, -2.569310f, -10.153900f, 3.930010f, -1.020280f, 2.674050f, -5.946960f, 2.166400f, 5.612800f, -6.396890f, -2.058420f, -4.066860f, 1.149970f, 0.289178f, -7.835220f, 4.204550f, 3.069610f, -2.277380f, -6.339250f, -2.857960f, -1.127620f, -10.779800f, -3.317880f, 3.486030f, 1.287950f, 
	-6.323340f, -14.186800f, -4.725950f, -9.468040f, -5.811290f, 1.749210f, -1.074820f, -3.101090f, 1.067470f, -6.051850f, -8.309870f, -4.457540f, -5.852300f, -7.926610f, -1.565450f, -7.729120f, -9.046420f, -5.177600f, 1.268600f, -1.689610f, 2.526890f, -8.186210f, -6.546980f, 2.240910f, -4.141780f, -2.855690f, 
	10.339900f, 8.579000f, 8.690360f, 3.212830f, 11.704700f, -1.956080f, 2.992000f, -5.444230f, 1.847770f, 8.762990f, 3.209650f, -2.841810f, 5.938790f, 4.475010f, -1.315930f, 11.262300f, 5.210130f, -4.732660f, 0.508361f, 6.957410f, 13.542900f, 7.888160f, 3.526680f, 6.377140f, 5.903880f, 2.858550f, 
};

const float Z[2][26] = {
	1.157520f, 1.523760f, 1.067000f, 1.253760f, 1.532030f, 1.804780f, 1.249980f, 1.304130f, 1.471520f, 2.038770f, 1.023310f, 1.703490f, 1.703790f, -1.454540f, -0.194343f, -0.166979f, -0.384304f, -1.314640f, -0.085286f, -0.483911f, 0.682217f, -1.241220f, -0.453871f, -1.298010f, 0.127286f, -0.418573f, 
	0.160370f, -0.577198f, -0.945236f, 0.081155f, -0.381438f, -0.758155f, -0.062279f, -0.671471f, -0.361359f, -0.874492f, -0.031955f, -0.508578f, -1.672030f, 0.976826f, 0.890941f, 1.227410f, 1.061980f, 1.567560f, 1.464930f, 1.611030f, 0.929228f, 1.758300f, 1.666040f, 0.928891f, 1.535850f, 1.099810f, 
};

}
