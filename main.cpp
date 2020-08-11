#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QApplication>
#include <QPushButton>
#include <iostream>

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkAutoInit.h>

//#include <engine.h>
//#include <testTtt.h>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	w.show();
    return a.exec();
}
