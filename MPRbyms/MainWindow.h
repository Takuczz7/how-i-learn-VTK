#ifndef MainWindow_H
#define MainWindow_H

#include "vtkSmartPointer.h"
#include "vtkResliceImageViewer.h"
#include "vtkImagePlaneWidget.h"
#include "vtkDistanceWidget.h"
#include "vtkResliceImageViewerMeasurements.h"
#include <QMainWindow>
#include "vtkDICOMImageReader.h"
#include <QtWidgets/QPushButton>
#include"vtkEventQtSlotConnect.h"
#include "ui_MainWindow.h"
#include "vtkImageActor.h"
#include "vtkMatrix4x4.h"
#include "vtkImageMapper3D.h"
#include "vtkCommand.h"

class Ui_MainWindow;
class vtkResliceCallback;

class MainWindow : public QMainWindow
{
	Q_OBJECT



public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	public slots:

	
	virtual void reslice(int);
	virtual void ResetViews();
	virtual void Render();

	
protected:
	vtkSmartPointer< vtkResliceImageViewer > riw[3];
	vtkSmartPointer< vtkImagePlaneWidget > planeWidget[3];

protected slots:
private:

	// Designer form
	Ui_MainWindow *ui;
	vtkSmartPointer<vtkDICOMImageReader> reader;
	vtkSmartPointer<vtkDICOMImageReader> original_data;
	vtkSmartPointer<vtkMatrix4x4>resliceAxes_C;
	vtkSmartPointer<vtkMatrix4x4>resliceAxes_A;
	vtkSmartPointer<vtkMatrix4x4>resliceAxes_S;
	vtkSmartPointer<vtkImageReslice>ImageReslice_C;
	vtkSmartPointer<vtkImageReslice>ImageReslice_A;
	vtkSmartPointer<vtkImageReslice>ImageReslice_S;
	vtkSmartPointer<vtkImageActor>imageActor_C; 
	vtkSmartPointer<vtkImageActor>imageActor_A;
	vtkSmartPointer<vtkImageActor>imageActor_S;
	vtkSmartPointer< vtkRenderer > aRendererA;
	vtkSmartPointer< vtkRenderWindow > renWinA;
	vtkSmartPointer< vtkRenderWindowInteractor > irenA;
	vtkSmartPointer< vtkRenderer > aRendererC;
	vtkSmartPointer< vtkRenderWindow > renWinC;
	vtkSmartPointer< vtkRenderWindowInteractor > irenC;
	vtkSmartPointer< vtkRenderer > aRendererS;
	vtkSmartPointer< vtkRenderWindow > renWinS;
	vtkSmartPointer< vtkRenderWindowInteractor > irenS;
	vtkSmartPointer<vtkInteractorStyleImage>imageStyle_C;
	vtkSmartPointer<vtkInteractorStyleImage>imageStyle_S;
	vtkSmartPointer<vtkInteractorStyleImage>imageStyle_A;
	vtkSmartPointer<vtkResliceCallback>callback;
	vtkSmartPointer< vtkRenderer > aRenderer;
	vtkSmartPointer< vtkRenderWindow > renWin;
	vtkSmartPointer< vtkRenderWindowInteractor > iren;
	vtkSmartPointer<vtkInteractorStyleImage>imageStyle;
	vtkSmartPointer<vtkImageMapToColors>mapToColors_C;
	vtkSmartPointer<vtkImageMapToColors>mapToColors_S;
	vtkSmartPointer<vtkImageMapToColors>mapToColors_A;

	private slots:
	virtual void on_BtnExp_clicked();

};

#endif // MainWindow_H
