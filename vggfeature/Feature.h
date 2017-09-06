/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#ifndef FACER_FEATURE_H
#define FACER_FEATURE_H

#include <vector>
namespace cv
{
	class Mat;
}
namespace Facer
{
	class  Feature
	{
	public:
		 Feature(int feature_size);
		 virtual ~ Feature();
		 virtual bool genFeature(const cv::Mat& img, std::vector<float>& feature) const = 0;

	protected:
		 int feature_size_;
	private:
	};
	const std::string getCurrentTime();
}
#endif
