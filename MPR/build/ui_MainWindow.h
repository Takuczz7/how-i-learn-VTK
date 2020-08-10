/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVTKWidget *view1;
    QVTKWidget *view2;
    QVTKWidget *view3;
    QVTKWidget *view4;
    QCheckBox *resliceModeCheckBox;
    QPushButton *resetButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        view1 = new QVTKWidget(centralwidget);
        view1->setObjectName(QStringLiteral("view1"));
        view1->setGeometry(QRect(10, 10, 291, 261));
        view2 = new QVTKWidget(centralwidget);
        view2->setObjectName(QStringLiteral("view2"));
        view2->setGeometry(QRect(10, 290, 291, 261));
        view3 = new QVTKWidget(centralwidget);
        view3->setObjectName(QStringLiteral("view3"));
        view3->setGeometry(QRect(320, 290, 291, 261));
        view4 = new QVTKWidget(centralwidget);
        view4->setObjectName(QStringLiteral("view4"));
        view4->setGeometry(QRect(320, 10, 291, 261));
        resliceModeCheckBox = new QCheckBox(centralwidget);
        resliceModeCheckBox->setObjectName(QStringLiteral("resliceModeCheckBox"));
        resliceModeCheckBox->setGeometry(QRect(660, 90, 91, 41));
        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(650, 150, 91, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        resliceModeCheckBox->setText(QApplication::translate("MainWindow", "reslice", 0));
        resetButton->setText(QApplication::translate("MainWindow", "reset", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
