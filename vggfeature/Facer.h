/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#ifndef FACER_FACER_H
#define FACER_FACER_H
#include <string>

#include <opencv2/opencv.hpp>

namespace Facer
{
	class Detector;
	class Feature;
	class DB;
	class Facer
	{
	public:
		Facer(Detector& detector, Feature& feature, DB& db);
		virtual ~Facer();
		virtual bool Register(cv::Mat& img, const std::string& name);
		virtual int Search(cv::Mat& query, cv::Rect& face_rect, std::string& name, std::string& imgname) const;
	protected:
		Detector& detector_;
		Feature& feature_;
		DB& db_;
	private:
		std::string img_dir_ = "../image/";
	};
}
#endif
