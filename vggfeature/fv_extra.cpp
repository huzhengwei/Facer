#include <iostream>
#include <string>
#include "CaffeBinding.h"

#include "LevelDB.h"
#include "MtcnnDetector.h"
#include "VggFeature.h"

caffe::CaffeBinding* kCaffeBinding = new caffe::CaffeBinding();
using namespace cv;
using namespace std;
using caffe::DataBlob;
using namespace FaceInception;

int main()
{
	//const string cascade_folder = "F:\\vs2008\\Caffe\\mtcnn-code\\codes\\MTCNNv2\\model\\";
	//Facer::MtcnnDetector mtcnn_detector_(cascade_folder);

	//Facer::VggFeature vggf("F:\\vs2008\\Caffe\\vgg_face_caffe\\", 4096);
	//auto img = imread("F:\\vs2008\\Caffe\\mtcnn-code\\codes\\MTCNNv2\\test1.jpg");
	//vector<float> fv;
	//vggf.genFeature(img, fv);

	Facer::LevelDB ldb("F:\\vs2008\\Caffe\\mtcnn-code\\codes\\vs\\DataBase");
	vector<float> f1 = { 3.14234f, -234.13f, -321.234f };
	vector<float> f2 = { 3, -200, -300 };
	string name = "hu", imgname = "20171012";
	ldb.insert(f1, name, imgname);
	cout << ldb.find(f2, name, imgname) + 1;


	float data[3] = {3.14234, -234.13, -321.234};
	char * c = (char*)data;
	string s(c, 3*sizeof(float));
	float *data_re = (float*)s.c_str();
	std::cout << data_re[0] << " " << data_re[1] << " " << data_re[2];



	/*auto img = imread("F:\\vs2008\\Caffe\\mtcnn-code\\codes\\MTCNNv2\\test1.jpg");
	cv::resize(img, img, cvSize(224, 224));
	string vggmodel_dir = "F:\\vs2008\\Caffe\\vgg_face_caffe\\";
	int net_vgg = kCaffeBinding->AddNet(vggmodel_dir+"VGG_FACE_deploy.prototxt",
										vggmodel_dir + "VGG_FACE.caffemodel", -1);
	auto vgg_output = kCaffeBinding->Forward({ img }, net_vgg);
	DataBlob fv = vgg_output["fc7"];
	cout << fv.name << endl; 
	cout << fv.size.size() << endl;
	for (int i = 0; i < 4096; ++i)
		cout << fv.data[i] << endl;*/
	return 0;
}
