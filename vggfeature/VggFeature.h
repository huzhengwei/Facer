/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#ifndef FACER_VGG_FEATURE_H
#define FACER_VGG_FEATURE_H

#include "Feature.h"

#include <string>

namespace Facer
{
	class VggFeature : public Feature
	{
	public:
		VggFeature(std::string model_dir, int feature_size);
		~VggFeature();
		bool VggFeature::genFeature(const cv::Mat& img, std::vector<float>& feature) const override;
	private:
		std::string model_dir_;
		int net_vgg_;
	};
}
#endif
