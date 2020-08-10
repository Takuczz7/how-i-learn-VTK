
#ifndef Project_MainWindow_H

#define Project_MainWindow_H



#include <QMainWindow>

#include "ui_ProjectMainWindow.h"



#include <vtkSmartPointer.h>



class vtkImageViewer2;

class vtkRenderer;

class QVTKWidget;
class vtkEventQtSlotConnect;



class ProjectMainWindow : public QMainWindow, public Ui::MainWindow

{

	Q_OBJECT



public:

	ProjectMainWindow();

	~ProjectMainWindow();



	private slots:

	//响应打开图像文件的槽函数

	void onOpenSlot();



private:

	vtkSmartPointer< vtkImageViewer2 > m_pImageViewer;

	vtkSmartPointer< vtkRenderer > m_pRenderder;
	
	
	vtkEventQtSlotConnect* m_Connections;
};



#endif
