/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#ifndef FACER_DETECTOR_H
#define FACER_DETECTOR_H

#include <opencv2/opencv.hpp>
namespace Facer
{
	class Detector
	{
	public:
		Detector();
		virtual ~Detector();
		virtual bool Detect(const cv::Mat& img, cv::Rect2d& rect) const = 0;
	private:
	};
}
#endif
