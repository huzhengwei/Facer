# Face recognition framework: Face detector, Face descriptor, Database

> Copyright (c) 2011 huzhengwei. All rights reserved. Author:huzhengwei, zhengwei_hu@163.com

> You can modifiy the code for you own feature by inherit the abstract class
## Requied
* QT
* C++11
* LevelDB
## 本工程：MTCNN人脸检测器与Vgg-Face特征、levelDB存储特征
## 各目录：
	DataBase: 数据库(使用LevelDB实现，保存姓名(即id)、vgg特征、图片路径)；
	image:注册图片保存；
	vgg_face_caffe: Vgg-Face模型参数；
	model: MTCNN模型参数；
	Facer: Facer主项目工程目录；
	vggfeature：人脸检测、人脸识别、数据库封装工程目录；
	Test: MTCNN功能测试（开源）
## 使用简介：
1. 进入x64_release-可执行文件入口，执行Facer.exe进入程序界面；
2. 程序自动加载模型参数，其状态在任务栏显示；这时你可以打开菜单栏->打开摄像头；
3. 程序会默认进入注册界面（实时），点击注册按钮即可注册；
4. 点击识别标签，有10s延时，请等待，出现画面之后即可识别（循环识别、跟踪显示）。
（因跟踪在相邻两次识别为同意id时进行，一次识别用时5s，所以跟踪需要延时10s显示）

## class：（均在命名空间Facer中）
	abstract class：（方便更改实现）
		DB：数据库抽象类别；
		Detector：人脸检测器抽象类别；
		Feature：特征提取抽象类别；
		Facer：注册与识别抽象类别，也是实现类；
	子类实现：
		LevelDB：LevelDB实现数据库；
		MtcnnDetector：MTCNN人脸检测算法；
		VggFeature:Vgg-Face特征；
	界面类：
		FaceRec：管理线程与空间；
[1] [MTCNN](https://github.com/happynear/MTCNN_face_detection_alignment/tree/master/code/codes/vs)
