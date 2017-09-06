/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
#include "FaceRec.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FaceRec w;
	w.setWindowFlags(w.windowFlags() &~(Qt::WindowMaximizeButtonHint));
	w.setFixedSize(742, 461);
	w.show();
	return a.exec();
}
