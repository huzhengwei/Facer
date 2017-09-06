/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#include "MtcnnDetector.h"

#include "TestFaceDetection.inc.h"

#include <utility>
#include <opencv2/opencv.hpp>

using FaceInception::CascadeCNN;

namespace Facer
{
	struct sortRectArea {
		bool operator () (const std::pair<cv::Rect2d, float> & a,
						  const std::pair<Rect2d, float> & b) {
			return a.first.width*a.first.height > b.first.width*b.first.height;
		}
	};
	
	MtcnnDetector::MtcnnDetector(const std::string& detector_dir) : detector_dir_(detector_dir)
	{
		cascade_cnn_ = new CascadeCNN(detector_dir + "det1-memory.prototxt", detector_dir + "det1.caffemodel",
			detector_dir + "det1-memory-stitch.prototxt", detector_dir + "det1.caffemodel",
			detector_dir + "det2-memory.prototxt", detector_dir + "det2.caffemodel",
			detector_dir + "det3-memory.prototxt", detector_dir + "det3.caffemodel",
			detector_dir + "det4-memory.prototxt", detector_dir + "det4.caffemodel",
			-1);
	}
	MtcnnDetector::~MtcnnDetector()
	{
		delete cascade_cnn_;
	}
	bool MtcnnDetector::Detect(const cv::Mat& img, cv::Rect2d& rect) const
	{
		double min_face_size = 24;
		auto result = cascade_cnn_->GetDetection(img.clone(), 12.0 / min_face_size, 0.7, true, 0.7, true);
		if (result.empty()) return false;
		sort(result.begin(), result.end(), sortRectArea());		
		rect =  result[0].first;
		return true;
	}
}