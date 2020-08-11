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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVTKWidget *qvtkWidget;
    QVTKWidget *qvtkWidget_A;
    QVTKWidget *qvtkWidget_C;
    QVTKWidget *qvtkWidget_S;
    QPushButton *pushButton_TDR;
    QPushButton *pushButton_TS;
    QPushButton *pushButton_R;
    QPushButton *pushButton_RS;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;
    QTextEdit *textEdit_4;
    QPushButton *pushButton_D;
    QTextBrowser *textBrowser;
    QTextEdit *textEdit_Low;
    QTextEdit *textEdit_Up;
    QPushButton *pushButton_S;
    QScrollBar *verticalScrollBar_A;
    QScrollBar *verticalScrollBar_C;
    QScrollBar *verticalScrollBar_S;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *textEdit_5;
    QTextEdit *textEdit_6;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(938, 872);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        qvtkWidget = new QVTKWidget(centralwidget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(0, 0, 471, 681));
        qvtkWidget_A = new QVTKWidget(centralwidget);
        qvtkWidget_A->setObjectName(QStringLiteral("qvtkWidget_A"));
        qvtkWidget_A->setGeometry(QRect(490, 0, 421, 221));
        qvtkWidget_C = new QVTKWidget(centralwidget);
        qvtkWidget_C->setObjectName(QStringLiteral("qvtkWidget_C"));
        qvtkWidget_C->setGeometry(QRect(490, 230, 421, 221));
        qvtkWidget_S = new QVTKWidget(centralwidget);
        qvtkWidget_S->setObjectName(QStringLiteral("qvtkWidget_S"));
        qvtkWidget_S->setGeometry(QRect(490, 460, 421, 221));
        pushButton_TDR = new QPushButton(centralwidget);
        pushButton_TDR->setObjectName(QStringLiteral("pushButton_TDR"));
        pushButton_TDR->setGeometry(QRect(10, 740, 75, 23));
        pushButton_TS = new QPushButton(centralwidget);
        pushButton_TS->setObjectName(QStringLiteral("pushButton_TS"));
        pushButton_TS->setGeometry(QRect(110, 710, 75, 23));
        pushButton_R = new QPushButton(centralwidget);
        pushButton_R->setObjectName(QStringLiteral("pushButton_R"));
        pushButton_R->setGeometry(QRect(10, 700, 75, 23));
        pushButton_RS = new QPushButton(centralwidget);
        pushButton_RS->setObjectName(QStringLiteral("pushButton_RS"));
        pushButton_RS->setGeometry(QRect(770, 690, 61, 111));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(620, 690, 61, 31));
        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(620, 730, 61, 31));
        textEdit_3 = new QTextEdit(centralwidget);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));
        textEdit_3->setGeometry(QRect(690, 690, 61, 31));
        textEdit_4 = new QTextEdit(centralwidget);
        textEdit_4->setObjectName(QStringLiteral("textEdit_4"));
        textEdit_4->setGeometry(QRect(690, 730, 61, 31));
        pushButton_D = new QPushButton(centralwidget);
        pushButton_D->setObjectName(QStringLiteral("pushButton_D"));
        pushButton_D->setGeometry(QRect(850, 690, 61, 111));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(220, 690, 321, 121));
        textEdit_Low = new QTextEdit(centralwidget);
        textEdit_Low->setObjectName(QStringLiteral("textEdit_Low"));
        textEdit_Low->setGeometry(QRect(150, 770, 61, 31));
        textEdit_Up = new QTextEdit(centralwidget);
        textEdit_Up->setObjectName(QStringLiteral("textEdit_Up"));
        textEdit_Up->setGeometry(QRect(90, 770, 61, 31));
        pushButton_S = new QPushButton(centralwidget);
        pushButton_S->setObjectName(QStringLiteral("pushButton_S"));
        pushButton_S->setGeometry(QRect(10, 780, 75, 23));
        verticalScrollBar_A = new QScrollBar(centralwidget);
        verticalScrollBar_A->setObjectName(QStringLiteral("verticalScrollBar_A"));
        verticalScrollBar_A->setGeometry(QRect(910, 0, 20, 221));
        verticalScrollBar_A->setOrientation(Qt::Vertical);
        verticalScrollBar_C = new QScrollBar(centralwidget);
        verticalScrollBar_C->setObjectName(QStringLiteral("verticalScrollBar_C"));
        verticalScrollBar_C->setGeometry(QRect(910, 230, 20, 221));
        verticalScrollBar_C->setOrientation(Qt::Vertical);
        verticalScrollBar_S = new QScrollBar(centralwidget);
        verticalScrollBar_S->setObjectName(QStringLiteral("verticalScrollBar_S"));
        verticalScrollBar_S->setGeometry(QRect(910, 460, 20, 221));
        verticalScrollBar_S->setOrientation(Qt::Vertical);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 750, 54, 12));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(160, 750, 54, 12));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(550, 700, 54, 12));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(550, 740, 54, 12));
        textEdit_5 = new QTextEdit(centralwidget);
        textEdit_5->setObjectName(QStringLiteral("textEdit_5"));
        textEdit_5->setGeometry(QRect(620, 770, 61, 31));
        textEdit_6 = new QTextEdit(centralwidget);
        textEdit_6->setObjectName(QStringLiteral("textEdit_6"));
        textEdit_6->setGeometry(QRect(690, 770, 61, 31));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(550, 780, 54, 12));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 938, 23));
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
        pushButton_TDR->setText(QApplication::translate("MainWindow", "\344\270\211\347\273\264\351\207\215\345\273\272", 0));
        pushButton_TS->setText(QApplication::translate("MainWindow", "\351\230\210\345\200\274\345\210\206\345\211\262", 0));
        pushButton_R->setText(QApplication::translate("MainWindow", "\351\200\211\345\217\226\346\226\207\344\273\266", 0));
        pushButton_RS->setText(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\210\206\345\211\262", 0));
        pushButton_D->setText(QApplication::translate("MainWindow", "\347\202\271\351\227\264\350\267\235", 0));
        pushButton_S->setText(QApplication::translate("MainWindow", "\346\226\255\345\261\202\345\233\276\345\203\217", 0));
        label->setText(QApplication::translate("MainWindow", "\344\270\212\351\230\210\345\200\274", 0));
        label_2->setText(QApplication::translate("MainWindow", "\344\270\213\351\230\210\345\200\274", 0));
        label_3->setText(QApplication::translate("MainWindow", "X\350\275\264\350\214\203\345\233\264\357\274\232", 0));
        label_4->setText(QApplication::translate("MainWindow", "Y\350\275\264\350\214\203\345\233\264\357\274\232", 0));
        label_5->setText(QApplication::translate("MainWindow", "Z\350\275\264\350\214\203\345\233\264\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
