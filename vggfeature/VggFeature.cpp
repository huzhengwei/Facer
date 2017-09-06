/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#include "VggFeature.h"

#include <vector>
#include "CaffeBinding.h"

extern caffe::CaffeBinding* kCaffeBinding;
using caffe::DataBlob;

namespace Facer
{
	VggFeature::VggFeature(std::string model_dir, int feature_size = 4096) :
		Feature(feature_size),
		model_dir_(model_dir), 
		net_vgg_( kCaffeBinding->AddNet(model_dir + "VGG_FACE_deploy.prototxt",
										model_dir + "VGG_FACE.caffemodel", -1))
	{

	}
	VggFeature::~VggFeature()
	{

	}
	bool VggFeature::genFeature(const cv::Mat& img, std::vector<float>& feature) const
	{
		cv::Mat img_resize;
		cv::resize(img, img_resize, cvSize(224, 224));
		auto vgg_output = kCaffeBinding->Forward({ img_resize }, net_vgg_);
		DataBlob fv = vgg_output["fc7"];
		feature = std::vector<float> (fv.data, fv.data+feature_size_);
		return true;
	}
}