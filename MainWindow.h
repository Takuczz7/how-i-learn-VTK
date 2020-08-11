#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <cstdio>
#include <QtWidgets/QPushButton>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "qfiledialog.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageActor.h"
#include "vtkImageShiftScale.h"
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkAutoInit.h>
#include <vtkImageData.h>
#include "vtkVolume16Reader.h"  
#include "vtkRenderWindowInteractor.h"   
#include "vtkMarchingCubes.h"  
#include "vtkStripper.h"  
#include "vtkActor.h"  
#include "vtkPolyDataMapper.h"  
#include "vtkProperty.h"  
#include "vtkCamera.h"  
#include "vtkBoxWidget.h"  
#include "vtkTriangleFilter.h"  
#include "vtkMassProperties.h" 
#include "vtkInteractorStyleTrackballCamera.h"
#include <vtkImageThreshold.h>
#include "vtkCommand.h"
#include"vtkEventQtSlotConnect.h"
namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();


	public slots:
	void open();
	void slotUpdateAxialSliceIndex(int);
	void slotUpdateCornalSliceIndex(int);
	void slotUpdateSagittalSliceIndex(int);
	void segmentBetween();
	void medianFilter();
	void DistanceB();
	
	private slots:
	void on_BtnExp_clicked();
	void slice();

	//void open();

private:
	Ui::MainWindow *ui;
	vtkSmartPointer<vtkDICOMImageReader> reader;
	vtkSmartPointer<vtkImageViewer2> imageViewerA;
	vtkSmartPointer<vtkImageViewer2> imageViewerC;
	vtkSmartPointer<vtkImageViewer2> imageViewerS;
	vtkSmartPointer<vtkImageThreshold> threshould;
	vtkSmartPointer<vtkDICOMImageReader> original_data;

	double *spacing;
	int *extent;

	bool flagA = false;
	bool flagC = false;
	bool flagS = false;
	vtkSmartPointer< vtkRenderer > aRendererA;
	vtkSmartPointer< vtkRenderWindow > renWinA;
	vtkSmartPointer< vtkRenderWindowInteractor > irenA;
	vtkSmartPointer< vtkRenderer > aRendererC;
	vtkSmartPointer< vtkRenderWindow > renWinC;
	vtkSmartPointer< vtkRenderWindowInteractor > irenC;
	vtkSmartPointer< vtkRenderer > aRendererS;
	vtkSmartPointer< vtkRenderWindow > renWinS;
	vtkSmartPointer< vtkRenderWindowInteractor > irenS;
};

#endif // MAINWINDOW_H
