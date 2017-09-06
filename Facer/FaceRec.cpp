/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#include "FaceRec.h"

#include "CaffeBinding.h"
#include "MtcnnDetector.h"
#include "LevelDB.h"
#include "VggFeature.h"
#include "Facer.h"

#include <qmessagebox.h>

caffe::CaffeBinding* kCaffeBinding = new caffe::CaffeBinding();



FaceRec::FaceRec(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.tabWidget->setCurrentIndex(1);
	connect(ui.openCamera, SIGNAL(triggered()), this, SLOT(openCamera()));
	connect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(currentTab(int)));
	connect(ui.btn_register_, SIGNAL(clicked()), this, SLOT(btn_register()));

	sttbar_label_ = new QLabel(this);
	ui.statusBar->addWidget(sttbar_label_);
	thd_initmodels_ = std::thread(&FaceRec::initModels, this);
}

FaceRec::~FaceRec()
{
	stop_vc_ = true;
	continue_recog_ = false;
	if (thd_regist_.joinable()) thd_regist_.join();
	if (thd_recog_.joinable()) thd_recog_.join();
	if (thd_vc_.joinable()) 	thd_vc_.join();
	if (thd_initmodels_.joinable()) thd_initmodels_.join();

	delete sttbar_label_;
	if(db_ != nullptr) delete db_;
	if(mtcnn_detector_!= nullptr) delete mtcnn_detector_;
	if(mtcnn_detector_!= nullptr) delete vgg_feature_;
	if(facer_ != nullptr)delete facer_;
	
}
void FaceRec::openCamera()
{
	if (vc_.open(0))
	{
		thd_vc_ = std::thread(&FaceRec::showPicture, this);
		ui.openCamera->setEnabled(false);
	}
	else
		QMessageBox::about(NULL, "Camera", "Camera open operarion failed!");
	
}
void FaceRec::showPicture()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));// waiting for camera 
	while (!stop_vc_)
	{
		cv::Mat bgr_img;
		{
			std::unique_lock<std::mutex> lck(img_mutex_);
			vc_ >> img_;
			
			img_.copyTo(bgr_img);
		}
		++img_ind_;

		cv::Mat show_img;
		cv::Rect show_rect;
		if (continue_recog_)
		{
			if (img_queue_.empty()) topimg_ind_ = img_ind_;
			img_queue_.push(bgr_img);
			{
				std::unique_lock<std::mutex> lck(snap_mutex_);
				if (img_queue_.size() > 300)
				{
					show_img = img_queue_.front();
					img_queue_.pop();
					if (snap_queue_.size() >= 2)
					{
						if (topimg_ind_ >= snap_queue_[1].frame_num_)
						{
							snap_queue_.erase(snap_queue_.begin());
						}
						else if (topimg_ind_ >= snap_queue_[0].frame_num_)
						{
							if (snap_queue_[0].result_ == 2 &&
								snap_queue_[1].result_ == 2 &&
								snap_queue_[0].name_ == snap_queue_[1].name_
								)
							{
								//插值,画矩形,显示人脸
								show_rect = interpolateRect(snap_queue_[0].rect_face_,
									snap_queue_[1].rect_face_, snap_queue_[1].frame_num_ - snap_queue_[0].frame_num_,
									topimg_ind_ - snap_queue_[0].frame_num_);
								cv::rectangle(show_img, show_rect, cv::Scalar(255, 0, 0), 3);

								showImage(show_img(show_rect).clone(), ui.label_face_, QSize(120, 120));
								cv::Mat person_img = cv::imread(snap_queue_[0].imgname_);
								showImage(person_img, ui.label_result_, QSize(160, 120));
								ui.text_name_->setText(QString::fromStdString(snap_queue_[0].name_));
								//if (result == 0)
								//{
								//	ui.text_name_->setText("No face detect!");
								//	ui.label_face_->clear();
								//	ui.label_result_->clear();
								//}
								//else
								//{
								//	showImage(full_img, ui.label_face_, QSize(120, 120));
								//	if (result == 1)
								//	{
								//		ui.text_name_->setText("No person matched!");
								//		ui.label_result_->clear();
								//	}
								//	if (result == 2)
								//	{
								//		cv::Mat person_img = cv::imread(imgname);
								//		showImage(person_img, ui.label_result_, QSize(160, 120));
								//		ui.text_name_->setText(QString::fromStdString(name));
								//	}
								//}
							}
							else
							{
								ui.text_name_->setText("No person matched!");
								ui.label_face_->clear();
								ui.label_result_->clear();
							}

						}
					}
					showImage(show_img, ui.label_camera_, QSize(300, 230));
					++topimg_ind_;
				}
				else
				{
					ui.label_camera_->clear();
				}
			}
		}
		else {
			if(!img_queue_.empty()) img_queue_.swap(std::queue<cv::Mat>());
			show_img = bgr_img;
			showImage(show_img, ui.label_camera_, QSize(300, 230));
		}
		


		//showImage(bgr_img, ui.label_camera_, QSize(300, 230));
	}
}

void FaceRec::initModels()
{
	const std::string cascade_folder = "..\\model\\";

	sttbar_label_->setText("loading detector models ......");
	db_ = new Facer::LevelDB("..\\DataBase");
	mtcnn_detector_ = new Facer::MtcnnDetector(cascade_folder);
	sttbar_label_->setText("loading feature models ......");
	vgg_feature_ = new Facer::VggFeature("..\\vgg_face_caffe\\", 4096);
	facer_ = new Facer::Facer(*mtcnn_detector_, *vgg_feature_, *db_);
	sttbar_label_->setText("models loaded!");
	is_inited_ = true;
}

void FaceRec::currentTab(int index)
{
	switch (index)
	{
	case 0:
		if (!is_inited_)
		{
			QMessageBox::about(NULL, "Please waiting", "Waiting for models loading...");
			ui.tabWidget->setCurrentIndex(1);
			break;
		}
		if (!stop_regist_)
		{
			QMessageBox::about(NULL, "Please waiting", "Waiting for registing...");
			ui.tabWidget->setCurrentIndex(1);
			break;
		}
		if (!stop_recog_ )
		{
			break;
		}
		continue_recog_ = true;
		thd_recog_ = std::thread(&FaceRec::beginRecognition, this);
		break;
	case 1:
		stopRecognition();
		break;
	}
}

void FaceRec::beginRecognition()
{
	while (continue_recog_)
	{
		int img_ind = img_ind_;
		stop_recog_ = false;
		sttbar_label_->setText("Begin recognition ......");
		cv::Mat full_img;
		{
			std::unique_lock<std::mutex> lck(img_mutex_);
			img_.copyTo(full_img);
		}
		std::string name, imgname;
		cv::Rect face_rect;
		int result = facer_->Search(full_img, face_rect, name, imgname);

		{
			std::unique_lock<std::mutex> lck(snap_mutex_);
			snap_queue_.push_back(snapNode(img_ind , result, name, imgname, face_rect));
		}
		//if (result == 0)
		//{
		//	ui.text_name_->setText("No face detect!");
		//	ui.label_face_->clear();
		//	ui.label_result_->clear();
		//}
		//else
		//{
		//	showImage(full_img, ui.label_face_, QSize(120, 120));
		//	if (result == 1)
		//	{
		//		ui.text_name_->setText("No person matched!");
		//		ui.label_result_->clear();
		//	}
		//	if (result == 2)
		//	{
		//		cv::Mat person_img = cv::imread(imgname);
		//		showImage(person_img, ui.label_result_, QSize(160, 120));
		//		ui.text_name_->setText(QString::fromStdString(name));
		//	}
		//}
		stop_recog_ = true;
	}
	ui.tabWidget->setCurrentIndex(1);

}

void FaceRec::stopRecognition()
{
	continue_recog_ = false;
	//if (!stop_recog_)
	//{
	//	QMessageBox::about(NULL, "Please waiting", "Waiting for recognition...");
	//	ui.tabWidget->setCurrentIndex(0);
	//	return;
	//}
	if (thd_recog_.joinable())
	{
		sttbar_label_->setText("Waiting for recognition close ......");
		thd_recog_.join();
		sttbar_label_->setText("Recognition closed! You can begin registion!");
		ui.label_face_->clear();
	}
}

void FaceRec::btn_register()
{
	if (!is_inited_)
	{
		QMessageBox::about(NULL, "Please waiting", "Waiting for models loading...");
		return;
	}
	std::string name = ui.input_name_->text().toStdString();
	if (name.empty())
	{
		QMessageBox::about(NULL, "No string", "Please input your name!");
		return ;
	}
	if (thd_regist_.joinable()) thd_regist_.join();
	thd_regist_ = std::thread(&FaceRec::registion, this);
}

void FaceRec::registion()
{
	std::string name = ui.input_name_->text().toStdString();
	stop_regist_ = false;
	ui.btn_register_->setEnabled(false);
	cv::Mat full_img;
	{
		std::unique_lock<std::mutex> lck(img_mutex_);
		img_.copyTo(full_img);
	}
	if (facer_->Register(full_img, name))
	{
		sttbar_label_->setText("Register finished!");
		showImage(full_img, ui.label_face_, QSize(120, 120));
		ui.input_name_->setText("Register finished!");
	}
	else
	{
		sttbar_label_->setText("No face detect!");
		ui.label_face_->clear();
	}
	ui.btn_register_->setEnabled(true);
	stop_regist_ = true;
}

void FaceRec::showImage(cv::Mat& img, QLabel *label, QSize size)
{
	QImage qimg;
	cv::cvtColor(img, img, CV_BGR2RGB);
	qimg = QImage((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
	qimg = qimg.scaled(size);
	label->setPixmap(QPixmap::fromImage(qimg));
}

cv::Rect FaceRec::interpolateRect(const cv::Rect& ls, const cv::Rect& rs, int size, int pos)
{
	cv::Rect rect;
	rect.x = ls.x + (static_cast<double>(pos) / size)*(rs.x - ls.x);
	rect.y = ls.y + (static_cast<double>(pos) / size)*(rs.y - ls.y);
	rect.width = ls.width + (static_cast<double>(pos) / size)*(rs.width - ls.width);
	rect.height = ls.height + (static_cast<double>(pos) / size)*(rs.height - ls.height);
	return std::move(rect);
}