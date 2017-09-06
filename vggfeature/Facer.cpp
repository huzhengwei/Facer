/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#include "Facer.h"

#include <filesystem>
#include <iomanip>
#include <vector>
#include <opencv2/opencv.hpp>

#include "Detector.h"
#include "DB.h"
#include "Feature.h"

namespace Facer
{
	Facer::Facer(Detector& detector, Feature& feature, DB& db) : 
		detector_(detector), feature_(feature), db_(db)
	{

	}
	Facer::~Facer()
	{

	}
	bool Facer::Register(cv::Mat& img, const std::string& name)
	{
		cv::Rect2d rect;
		if (!detector_.Detect(img, rect)) return false;
		cv::Mat face_img = img(rect);
		std::vector<float> face_feature;
		feature_.genFeature(face_img, face_feature);
		std::string imgname = getCurrentTime();
		db_.insert(face_feature, name, imgname);
		cv::imwrite(img_dir_ + imgname + ".jpg", img);

		img = face_img;
		return true;
	}
	int Facer::Search(cv::Mat& query, cv::Rect& face_rect, std::string& name, std::string& imgname) const
	{
		cv::Rect2d rect;
		if (!detector_.Detect(query, rect)) return 0; // no face
		cv::Rect i_rect(rect);
		i_rect = i_rect & cv::Rect(0, 0, query.cols, query.rows);
		cv::Mat face_img = query(i_rect);
		std::vector<float> face_feature;
		feature_.genFeature(face_img, face_feature);
		int res = db_.find(face_feature, name, imgname);
		imgname = img_dir_ + imgname + ".jpg";

		query = face_img;
		face_rect = i_rect;
		return res + 1;// 1:have face but no person
					// 2:have face and have person
	}
	

	const std::string getCurrentTime()
	{
		std::stringstream ss;
		ss.clear();
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		ss << std::put_time(std::localtime(&now_c), "%Y%m%d%H%M%S");
		std::string str_time;
		ss >> str_time;
		return std::move(str_time);
	}
}