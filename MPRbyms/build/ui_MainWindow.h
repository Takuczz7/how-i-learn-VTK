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
    QVTKWidget *qvtkWidget;
    QVTKWidget *qvtkWidget_2;
    QVTKWidget *qvtkWidget_3;
    QVTKWidget *qvtkWidget_4;
    QPushButton *pushButton_Read;
    QCheckBox *checkBox;
    QPushButton *pushButton_Reset;
    QCheckBox *checkBox_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(530, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        qvtkWidget = new QVTKWidget(centralwidget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(0, 0, 261, 231));
        qvtkWidget_2 = new QVTKWidget(centralwidget);
        qvtkWidget_2->setObjectName(QStringLiteral("qvtkWidget_2"));
        qvtkWidget_2->setGeometry(QRect(0, 240, 261, 231));
        qvtkWidget_3 = new QVTKWidget(centralwidget);
        qvtkWidget_3->setObjectName(QStringLiteral("qvtkWidget_3"));
        qvtkWidget_3->setGeometry(QRect(270, 0, 261, 231));
        qvtkWidget_4 = new QVTKWidget(centralwidget);
        qvtkWidget_4->setObjectName(QStringLiteral("qvtkWidget_4"));
        qvtkWidget_4->setGeometry(QRect(270, 240, 261, 231));
        pushButton_Read = new QPushButton(centralwidget);
        pushButton_Read->setObjectName(QStringLiteral("pushButton_Read"));
        pushButton_Read->setGeometry(QRect(10, 490, 81, 51));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(430, 480, 71, 31));
        pushButton_Reset = new QPushButton(centralwidget);
        pushButton_Reset->setObjectName(QStringLiteral("pushButton_Reset"));
        pushButton_Reset->setGeometry(QRect(420, 530, 75, 23));
        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(430, 500, 71, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 530, 23));
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
        pushButton_Read->setText(QApplication::translate("MainWindow", "\351\200\211\345\217\226\346\226\207\344\273\266", 0));
        checkBox->setText(QApplication::translate("MainWindow", "\346\227\213\350\275\254", 0));
        pushButton_Reset->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256", 0));
        checkBox_2->setText(QApplication::translate("MainWindow", "\345\271\263\347\247\273", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
