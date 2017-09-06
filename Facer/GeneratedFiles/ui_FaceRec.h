/********************************************************************************
** Form generated from reading UI file 'FaceRec.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEREC_H
#define UI_FACEREC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FaceRecClass
{
public:
    QAction *openCamera;
    QWidget *centralWidget;
    QLabel *label_camera_;
    QLabel *label_face_;
    QLabel *label_5;
    QTabWidget *tabWidget;
    QWidget *tab_recog_;
    QLabel *label_4;
    QLineEdit *text_name_;
    QLabel *label_8;
    QLabel *label_result_;
    QWidget *tab_register_;
    QLineEdit *input_name_;
    QLabel *label_6;
    QPushButton *btn_register_;
    QLabel *label_7;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FaceRecClass)
    {
        if (FaceRecClass->objectName().isEmpty())
            FaceRecClass->setObjectName(QStringLiteral("FaceRecClass"));
        FaceRecClass->setWindowModality(Qt::NonModal);
        FaceRecClass->setEnabled(true);
        FaceRecClass->resize(742, 461);
        openCamera = new QAction(FaceRecClass);
        openCamera->setObjectName(QStringLiteral("openCamera"));
        centralWidget = new QWidget(FaceRecClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_camera_ = new QLabel(centralWidget);
        label_camera_->setObjectName(QStringLiteral("label_camera_"));
        label_camera_->setGeometry(QRect(10, 60, 311, 301));
        label_face_ = new QLabel(centralWidget);
        label_face_->setObjectName(QStringLiteral("label_face_"));
        label_face_->setGeometry(QRect(360, 20, 121, 121));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(360, 0, 61, 16));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(330, 150, 371, 251));
        tab_recog_ = new QWidget();
        tab_recog_->setObjectName(QStringLiteral("tab_recog_"));
        label_4 = new QLabel(tab_recog_);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(220, 50, 54, 12));
        text_name_ = new QLineEdit(tab_recog_);
        text_name_->setObjectName(QStringLiteral("text_name_"));
        text_name_->setGeometry(QRect(220, 100, 131, 21));
        label_8 = new QLabel(tab_recog_);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 20, 61, 16));
        label_result_ = new QLabel(tab_recog_);
        label_result_->setObjectName(QStringLiteral("label_result_"));
        label_result_->setGeometry(QRect(10, 40, 161, 121));
        tabWidget->addTab(tab_recog_, QString());
        tab_register_ = new QWidget();
        tab_register_->setObjectName(QStringLiteral("tab_register_"));
        tab_register_->setFocusPolicy(Qt::NoFocus);
        tab_register_->setContextMenuPolicy(Qt::DefaultContextMenu);
        input_name_ = new QLineEdit(tab_register_);
        input_name_->setObjectName(QStringLiteral("input_name_"));
        input_name_->setGeometry(QRect(20, 100, 131, 21));
        label_6 = new QLabel(tab_register_);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 50, 54, 12));
        btn_register_ = new QPushButton(tab_register_);
        btn_register_->setObjectName(QStringLiteral("btn_register_"));
        btn_register_->setGeometry(QRect(220, 90, 101, 31));
        tabWidget->addTab(tab_register_, QString());
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 20, 61, 16));
        FaceRecClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FaceRecClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 742, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        FaceRecClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FaceRecClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FaceRecClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FaceRecClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FaceRecClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(openCamera);

        retranslateUi(FaceRecClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FaceRecClass);
    } // setupUi

    void retranslateUi(QMainWindow *FaceRecClass)
    {
        FaceRecClass->setWindowTitle(QApplication::translate("FaceRecClass", "FaceRec", Q_NULLPTR));
        openCamera->setText(QApplication::translate("FaceRecClass", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        label_camera_->setText(QString());
        label_face_->setText(QString());
        label_5->setText(QApplication::translate("FaceRecClass", "\344\272\272\350\204\270\346\243\200\346\265\213:", Q_NULLPTR));
        label_4->setText(QApplication::translate("FaceRecClass", "\345\247\223\345\220\215:", Q_NULLPTR));
        label_8->setText(QApplication::translate("FaceRecClass", "\350\257\206\345\210\253\347\273\223\346\236\234:", Q_NULLPTR));
        label_result_->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_recog_), QApplication::translate("FaceRecClass", "\350\257\206\345\210\253", Q_NULLPTR));
#ifndef QT_NO_ACCESSIBILITY
        tab_register_->setAccessibleName(QApplication::translate("FaceRecClass", "<html><head/><body><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_ACCESSIBILITY
        input_name_->setText(QString());
        label_6->setText(QApplication::translate("FaceRecClass", "\350\276\223\345\205\245\345\247\223\345\220\215:", Q_NULLPTR));
        btn_register_->setText(QApplication::translate("FaceRecClass", "\346\263\250\345\206\214", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_register_), QApplication::translate("FaceRecClass", "\346\263\250\345\206\214", Q_NULLPTR));
        label_7->setText(QApplication::translate("FaceRecClass", "\346\221\204\345\203\217\345\244\264:", Q_NULLPTR));
        menu->setTitle(QApplication::translate("FaceRecClass", "\350\217\234\345\215\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FaceRecClass: public Ui_FaceRecClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEREC_H
