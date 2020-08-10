
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

	

	// ����m_QVTKWidget����Ⱦ��

	qvtkWidget->GetRenderWindow()->AddRenderer(m_pRenderder);



	//���Ӵ򿪵��ź�����Ӧ�Ĳ�

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

		QString(tr("��ͼ��")), dir.absolutePath(), filter);

	if (fileName.isEmpty() == true) return;



	// ֧�ִ�����·���Ķ�ȡ

	QByteArray ba = fileName.toLocal8Bit();

	const char *fileName_str = ba.data();



	// ��vtkJPEGReader��ȡJPGͼ��

	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();

	reader->SetFileName(fileName_str);
	reader->Update();


	// ��reader�������Ϊm_pImageViewer�����룬������m_pImageViewer����Ⱦ��m_pRenderer�Ĺ���

	m_pImageViewer->SetInputData(reader->GetOutput());

	m_pImageViewer->UpdateDisplayExtent();

	m_pImageViewer->SetRenderWindow(qvtkWidget->GetRenderWindow());

	m_pImageViewer->SetRenderer(m_pRenderder);

	m_pImageViewer->SetupInteractor(qvtkWidget->GetRenderWindow()->GetInteractor());

	m_pImageViewer->SetSliceOrientationToXY(); //Ĭ�Ͼ�����������

	m_pImageViewer->GetImageActor()->InterpolateOff();

	m_pRenderder->ResetCamera();

	m_pRenderder->DrawOn();

	qvtkWidget->GetRenderWindow()->Render();

}
