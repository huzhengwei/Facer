#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FaceRec.h"

#include <queue>
#include <atomic>
#include <thread>
#include <mutex>
#include <opencv2/opencv.hpp>

struct snapNode
{
	int frame_num_;
	int result_;
	std::string name_;
	std::string imgname_;
	cv::Rect rect_face_;
	snapNode(int frame_num, int result, const std::string& name,
		     const std::string& imgname, const cv::Rect& rect_face)
		: frame_num_(frame_num), result_(result), 
		name_(name), imgname_(imgname), rect_face_(rect_face)
	{
		
	}
};

namespace FaceInception
{
	class CascadeCNN;
}
namespace Facer
{
	class Detector;
	class Feature;
	class DB;
	class Facer;

}
class FaceRec : public QMainWindow
{
	Q_OBJECT

public:
	FaceRec(QWidget *parent = Q_NULLPTR);
	~FaceRec();

private slots:
	void openCamera();
	void currentTab(int index);
	void btn_register();

private:
	void initModels();
	void showPicture();
	void beginRecognition();
	void stopRecognition();
	void registion();
	void showImage(cv::Mat& img, QLabel *label, QSize size);
	cv::Rect interpolateRect(const cv::Rect& ls, const cv::Rect& rs, int size, int pos);

	Ui::FaceRecClass ui;

	cv::VideoCapture vc_;

	std::vector<snapNode> snap_queue_;// detect and recognition snapshot
	std::mutex snap_mutex_;

	std::queue<cv::Mat> img_queue_;
	std::atomic<int> img_ind_ = 0;
	int topimg_ind_ = 0;

	std::atomic<bool> continue_recog_ = false;
	std::atomic<bool> stop_vc_ = false;
	std::thread thd_vc_;

	std::thread thd_initmodels_;
	std::atomic<bool> is_inited_ = false;

	std::atomic<bool> stop_recog_ = true;
	std::thread thd_recog_;

	std::thread thd_regist_;
	std::atomic<bool> stop_regist_ = true;

	cv::Mat img_;
	std::mutex img_mutex_;

	Facer::Detector* mtcnn_detector_;
	Facer::Feature* vgg_feature_;
	Facer::DB* db_;
	Facer::Facer * facer_;

	QLabel* sttbar_label_;
};
