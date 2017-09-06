/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#ifndef FACER_MTCNN_DETECTOR_H
#define FACER_MTCNN_DETECTOR_H

#include "Detector.h"
#include <string>
namespace FaceInception
{
	class CascadeCNN;
}
namespace Facer
{
	class MtcnnDetector : public Detector
	{
	public:
		MtcnnDetector(const std::string& detector_dir);
		~MtcnnDetector();
		bool Detect(const cv::Mat& img, cv::Rect2d& rect) const override;
	private:
		FaceInception::CascadeCNN * cascade_cnn_;
		const std::string& detector_dir_;
	};
}
#endif
