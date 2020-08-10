
#include "ProjectMainWindow.h"



#include <QFileDialog>

#include <QDir>



#include <vtkRenderWindow.h>

#include <vtkRenderer.h>

#include <vtkImageViewer2.h>

#include <QVTKWidget.h>

#include <vtkJPEGReader.h>

#include <vtkImageActor.h>
#include <vtkEventQtSlotConnect.h>


ProjectMainWindow::ProjectMainWindow()

{

	setupUi(this);



	m_pImageViewer = vtkSmartPointer< vtkImageViewer2 >::New();

	m_pRenderder = vtkSmartPointer< vtkRenderer >::New();

	

	// 设置m_QVTKWidget的渲染器

	qvtkWidget->GetRenderWindow()->AddRenderer(m_pRenderder);



	//连接打开的信号与相应的槽

	//connect(m_OpenAction, SIGNAL(triggered()), this, SLOT(onOpenSlot()));
	m_Connections = vtkEventQtSlotConnect::New();
}



ProjectMainWindow::~ProjectMainWindow()

{

}



void ProjectMainWindow::onOpenSlot()

{

	QString filter;

	filter = "JPEG image file (*.jpg *.jpeg)";



	QDir dir;

	QString fileName = QFileDialog::getOpenFileName(this,

		QString(tr("打开图像")), dir.absolutePath(), filter);

	if (fileName.isEmpty() == true) return;



	// 支持带中文路径的读取

	QByteArray ba = fileName.toLocal8Bit();

	const char *fileName_str = ba.data();



	// 用vtkJPEGReader读取JPG图像

	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();

	reader->SetFileName(fileName_str);
	reader->Update();


	// 将reader的输出作为m_pImageViewer的输入，并设置m_pImageViewer与渲染器m_pRenderer的关联

	m_pImageViewer->SetInputData(reader->GetOutput());

	m_pImageViewer->UpdateDisplayExtent();

	m_pImageViewer->SetRenderWindow(qvtkWidget->GetRenderWindow());

	m_pImageViewer->SetRenderer(m_pRenderder);

	m_pImageViewer->SetupInteractor(qvtkWidget->GetRenderWindow()->GetInteractor());

	m_pImageViewer->SetSliceOrientationToXY(); //默认就是这个方向的

	m_pImageViewer->GetImageActor()->InterpolateOff();

	m_pRenderder->ResetCamera();

	m_pRenderder->DrawOn();

	qvtkWidget->GetRenderWindow()->Render();

}
