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
#include <vtkNamedColors.h>
#include<array>
#include<vtkEventQtSlotConnect.h>
#include "vtkCommand.h"
#include"vtkPropPicker.h"
#include "vtkCornerAnnotation.h"
#include <vtkVersion.h>
#include <vtkAssemblyPath.h>
#include <vtkCell.h>
#include <vtkDataArray.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkTextProperty.h>
#include <vtkInteractorStyleImage.h>
#include<stdlib.h>
#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//建立与插槽的连接
	connect(ui->pushButton_R, SIGNAL(clicked()), this, SLOT(on_BtnExp_clicked()));
	connect(ui->pushButton_TDR, SIGNAL(clicked()), this, SLOT(open()));
	connect(ui->pushButton_S, SIGNAL(clicked()), this, SLOT(slice()));
	connect(ui->verticalScrollBar_A, SIGNAL(valueChanged(int)), this, SLOT(slotUpdateAxialSliceIndex(int)));
	connect(ui->verticalScrollBar_C, SIGNAL(valueChanged(int)), this, SLOT(slotUpdateCornalSliceIndex(int)));
	connect(ui->verticalScrollBar_S, SIGNAL(valueChanged(int)), this, SLOT(slotUpdateSagittalSliceIndex(int)));
	connect(ui->pushButton_TS, SIGNAL(clicked()), this, SLOT(segmentBetween()));
	connect(ui->pushButton_RS, SIGNAL(clicked()), this, SLOT(medianFilter()));
	connect(ui->pushButton_D, SIGNAL(clicked()), this, SLOT(DistanceB()));

}
MainWindow::~MainWindow()
{
	delete ui;
}
//读取文件部分
QString GetFileDirDLG()
{
	char* title = "Select Directory";
	char* defaultPath = "F:\\czz\\VHMCT1mm_Shoulder";//默认进入此路径选择
	char* defaultDIR = defaultPath;
	return QFileDialog::getExistingDirectory(
		0,
		QString::fromLocal8Bit(title),
		QString::fromLocal8Bit(defaultDIR)
		);                                           //第三个参数指定某个路径（绝对/相对），对话框打开时默认进入此路径选择
}
class vtkImageInteractionCallbackA : public vtkCommand
{
public:

	static vtkImageInteractionCallbackA *New()
	{
		return new vtkImageInteractionCallbackA;
	}

	vtkImageInteractionCallbackA()
	{
		this->Viewer = 0;
		this->Picker = 0;
		this->Annotation = 0;
		this->PointData = vtkPointData::New();
	}

	~vtkImageInteractionCallbackA()
	{
		this->Viewer = 0;
		this->Picker = 0;
		this->Annotation = 0;
		this->PointData->Delete();
	}

	void SetPicker(vtkPropPicker *picker)
	{
		this->Picker = picker;
	}

	void SetAnnotation(vtkCornerAnnotation *annotation)
	{
		this->Annotation = annotation;
	}

	void SetViewer(vtkImageViewer2 *viewer)
	{
		this->Viewer = viewer;
	}

	virtual void Execute(vtkObject *, unsigned long vtkNotUsed(event), void *)
	{
		//this->Viewer;
		vtkRenderWindowInteractor *interactor =
			this->Viewer->GetRenderWindow()->GetInteractor();
		vtkRenderer* renderer = this->Viewer->GetRenderer();
		vtkImageActor* actor = this->Viewer->GetImageActor();
		vtkImageData* image = this->Viewer->GetInput();
		vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(
			interactor->GetInteractorStyle());

#if VTK_MAJOR_VERSION <= 5
		image->Update();
#endif

		// Pick at the mouse location provided by the interactor
		this->Picker->Pick(interactor->GetEventPosition()[0],interactor->GetEventPosition()[1],0.0, renderer);

		// There could be other props assigned to this picker, so 
		// make sure we picked the image actor
		vtkAssemblyPath* path = this->Picker->GetPath();
		bool validPick = false;

		if (path)
		{
			vtkCollectionSimpleIterator sit;
			path->InitTraversal(sit);
			vtkAssemblyNode *node;
			for (int i = 0; i < path->GetNumberOfItems() && !validPick; ++i)
			{
				node = path->GetNextNode(sit);
				if (actor == vtkImageActor::SafeDownCast(node->GetViewProp()))
				{
					validPick = true;
				}
			}
		}

		if (!validPick)
		{
			this->Annotation->SetText(0, "Off Image");
			interactor->Render();
			// Pass the event further on
			style->OnMouseMove();
			return;
		}

		// Get the world coordinates of the pick
		double pos[3];
		this->Picker->GetPickPosition(pos);
		// Fixes some numerical problems with the picking
		double *bounds = actor->GetDisplayBounds();
		int axis = this->Viewer->GetSliceOrientation();
		pos[axis] = bounds[2 * axis];

		vtkPointData* pd = image->GetPointData();
		if (!pd)
		{
			return;
		}

		this->PointData->InterpolateAllocate(pd, 1, 1);

		// Use tolerance as a function of size of source data
		double tol2 = image->GetLength();
		tol2 = tol2 ? tol2*tol2 / 1000.0 : 0.001;

		// Find the cell that contains pos
		int subId;
		double pcoords[3], weights[8];
		vtkCell* cell = image->FindAndGetCell(
			pos, NULL, -1, tol2, subId, pcoords, weights);
		if (cell)
		{
			// Interpolate the point data
			this->PointData->InterpolatePoint(pd, 0, cell->PointIds, weights);
			int components =
				this->PointData->GetScalars()->GetNumberOfComponents();
			double* tuple = this->PointData->GetScalars()->GetTuple(0);

			std::string message = "Location: ( ";
			message += vtkVariant(pos[0]).ToString();
			message += ", ";
			message += vtkVariant(pos[1]).ToString();
			message += ", ";
			message += vtkVariant(pos[2]).ToString();
			message += " )\nValue: ( ";

			for (int c = 0; c < components; ++c)
			{
				message += vtkVariant(tuple[c]).ToString();
				if (c != components - 1)
				{
					message += ", ";
				}
			}
			message += " )";
			this->Annotation->SetText(0, message.c_str());
			interactor->Render();
			style->OnMouseMove();
		}
	}

private:

	// Pointer to the viewer
	vtkImageViewer2 *Viewer;

	// Pointer to the picker
	vtkPropPicker *Picker;

	// Pointer to the annotation
	vtkCornerAnnotation *Annotation;

	// Interpolator
	vtkPointData* PointData;
};
void MainWindow::on_BtnExp_clicked()
{
	QString myPath = GetFileDirDLG();
	// 读取显示
	ui->textBrowser->setText("Loading...");
	reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetDirectoryName(myPath.toStdString().c_str());
	reader->Update();
	extent = reader->GetOutput()->GetExtent();
	ui->verticalScrollBar_A->setMaximum(extent[5]);
	ui->verticalScrollBar_C->setMaximum(extent[3]);
	ui->verticalScrollBar_S->setMaximum(extent[1]);


	threshould =
		vtkSmartPointer<vtkImageThreshold>::New();//阈值参数的设定
	original_data = vtkSmartPointer<vtkDICOMImageReader>::New();
	original_data = reader;
	threshould->SetInputConnection(reader->GetOutputPort());

	aRendererA = vtkSmartPointer< vtkRenderer >::New();
	renWinA = ui->qvtkWidget_A->GetRenderWindow();
	irenA = vtkSmartPointer< vtkRenderWindowInteractor >::New();
	irenA->SetRenderWindow(renWinA);
	aRendererC = vtkSmartPointer< vtkRenderer >::New();
	renWinC = ui->qvtkWidget_C->GetRenderWindow();
	irenC = vtkSmartPointer< vtkRenderWindowInteractor >::New();
	irenC->SetRenderWindow(renWinC);
	aRendererS = vtkSmartPointer< vtkRenderer >::New();
	renWinS = ui->qvtkWidget_S->GetRenderWindow();
	irenS = vtkSmartPointer< vtkRenderWindowInteractor >::New();
	irenS->SetRenderWindow(renWinS);

	imageViewerA = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewerA->SetInputConnection(threshould->GetOutputPort());
	imageViewerA->SetSliceOrientation(2);//修改参数为0，1，2可分别得到不同方向的切片
	imageViewerA->SetupInteractor(irenA);
	imageViewerA->SetRenderWindow(renWinA);
	imageViewerA->SetRenderer(aRendererA);
	imageViewerA->SetColorLevel(25);
	imageViewerA->SetColorWindow(3000);
	imageViewerA->GetRenderer()->ResetCamera();
	imageViewerA->GetRenderer()->GetActiveCamera()->Roll(0);
	imageViewerA->GetRenderer()->GetActiveCamera()->Yaw(180);
	imageViewerA->GetRenderer()->GetActiveCamera()->Elevation(180);
	imageViewerA->GetRenderer()->GetActiveCamera()->Zoom(6.0);
	

	imageViewerC = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewerC->SetInputConnection(threshould->GetOutputPort());
	imageViewerC->SetSliceOrientation(1);//修改参数为0，1，2可分别得到不同方向的切片
	imageViewerC->SetupInteractor(irenC);
	imageViewerC->SetRenderWindow(renWinC);
	imageViewerC->SetRenderer(aRendererC);
	imageViewerC->SetColorLevel(25);
	imageViewerC->SetColorWindow(3000);
	imageViewerC->GetRenderer()->ResetCamera();
	imageViewerC->GetRenderer()->GetActiveCamera()->Roll(180);
	imageViewerC->GetRenderer()->GetActiveCamera()->ParallelProjectionOn();
	imageViewerC->GetRenderer()->GetActiveCamera()->Elevation(180);
	imageViewerC->GetRenderer()->GetActiveCamera()->Zoom(1.0);


	imageViewerS = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewerS->SetInputConnection(threshould->GetOutputPort());
	imageViewerS->SetSliceOrientation(0);//修改参数为0，1，2可分别得到不同方向的切片
	imageViewerS->SetupInteractor(irenS);
	imageViewerS->SetRenderWindow(renWinS);
	imageViewerS->SetRenderer(aRendererS);
	imageViewerS->SetColorLevel(25);
	imageViewerS->SetColorWindow(3000);
	imageViewerS->GetRenderer()->ResetCamera();
	imageViewerS->GetRenderer()->GetActiveCamera()->Roll(180);
	imageViewerS->GetRenderer()->GetActiveCamera()->ParallelProjectionOn();
	imageViewerS->GetRenderer()->GetActiveCamera()->Elevation(180);
	imageViewerS->GetRenderer()->GetActiveCamera()->Zoom(1.0);
	
	ui->textBrowser->setText("Image has been loaded successfully.");
}

//三维重建部分
void MainWindow::open(){

	
	//抽取等值面为骨头的信息  
	vtkSmartPointer<vtkMarchingCubes> boneExtractor=
		vtkSmartPointer< vtkMarchingCubes >::New();
	boneExtractor->SetInputConnection(threshould->GetOutputPort());
	//boneExtractor->SetValue(0, 500); //设置提取的等值信息
	boneExtractor->SetValue(0, 200);
	boneExtractor->SetNumberOfContours(1);
	boneExtractor->Update();



	//建立映射  
	vtkSmartPointer< vtkPolyDataMapper > boneMapper =
		vtkSmartPointer< vtkPolyDataMapper >::New();
	boneMapper->SetInputData(boneExtractor->GetOutput());
	boneMapper->ScalarVisibilityOff();

	//设定颜色
	vtkSmartPointer<vtkNamedColors> colors =
		vtkSmartPointer<vtkNamedColors>::New();

	std::array<unsigned char, 4> skinColor{ { 255, 125, 64 } };
	colors->SetColor("SkinColor", skinColor.data());
	std::array<unsigned char, 4> bkg{ { 51, 77, 102, 255 } };
	colors->SetColor("BkgColor", bkg.data());
	//建立角色  
	vtkSmartPointer< vtkActor > bone =
		vtkSmartPointer< vtkActor >::New();
	bone->SetMapper(boneMapper);
	bone->GetProperty()->SetDiffuseColor(colors->GetColor3d("Ivory").GetData());
	bone->GetProperty()->SetSpecular(.3);
	bone->GetProperty()->SetSpecularPower(20);
	bone->GetProperty()->SetOpacity(1.0);
	bone->GetProperty()->SetColor(1, 1, 1);
	bone->GetProperty()->SetRepresentationToSurface();

	vtkSmartPointer<vtkMarchingCubes> skinExtractor =
		vtkSmartPointer<vtkMarchingCubes>::New();
	skinExtractor->SetInputConnection(threshould->GetOutputPort());
	skinExtractor->SetValue(0, -600);
	skinExtractor->SetNumberOfContours(1);
	skinExtractor->Update();


	vtkSmartPointer<vtkPolyDataMapper> skinMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	skinMapper->SetInputConnection(skinExtractor->GetOutputPort());
	skinMapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> skin =
		vtkSmartPointer<vtkActor>::New();
	skin->SetMapper(skinMapper);
	skin->GetProperty()->SetDiffuseColor(colors->GetColor3d("SkinColor").GetData());
	skin->GetProperty()->SetSpecular(.3);
	skin->GetProperty()->SetSpecularPower(20);
	skin->GetProperty()->SetOpacity(.5);
	//定义绘制器  
	vtkSmartPointer< vtkRenderer > aRenderer =
		vtkSmartPointer< vtkRenderer >::New();
	//定义绘制窗口  
	vtkSmartPointer< vtkRenderWindow > renWin = ui->qvtkWidget->GetRenderWindow();
	//vtkSmartPointer< vtkRenderWindow >::New();
	renWin->AddRenderer(aRenderer);

	//定义窗口交互器  
	vtkSmartPointer< vtkRenderWindowInteractor > iren =
		vtkSmartPointer< vtkRenderWindowInteractor >::New();
	iren->SetRenderWindow(renWin);

	//创建一个camera  
	vtkSmartPointer< vtkCamera > aCamera =
		vtkSmartPointer< vtkCamera >::New();
	aCamera->SetViewUp(0, 0, -1);
	aCamera->SetPosition(0, 1, 0);
	aCamera->SetFocalPoint(0, 0, 0);

	aRenderer->AddActor(bone);
	aRenderer->AddActor(skin);
	aRenderer->SetActiveCamera(aCamera);
	aRenderer->ResetCamera();
	aCamera->Dolly(1.5);
	aRenderer->SetBackground(0, 0, 0);
	aRenderer->ResetCameraClippingRange();

	vtkInteractorStyleTrackballCamera *style =       //设置交互方式
		vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);
	iren->Initialize();
	iren->Start();
}

//Reslice
void MainWindow::slice()
{
	
	spacing = reader->GetDataSpacing();
	flagA = true;
	imageViewerA->SetInputConnection(threshould->GetOutputPort());
	imageViewerA->SetSliceOrientation(2);//修改参数为0，1，2可分别得到不同方向的切片
	imageViewerA->Render();
	imageViewerA->SetSlice(extent[5] / 2);
	ui->verticalScrollBar_A->setValue(extent[5] / 2);
	vtkSmartPointer<vtkPropPicker> propPickerA =
		vtkSmartPointer<vtkPropPicker>::New();
	propPickerA->PickFromListOn();
	propPickerA->AddPickList(imageViewerA->GetImageActor());
	vtkSmartPointer<vtkCornerAnnotation> cornerAnnotationA =
		vtkSmartPointer<vtkCornerAnnotation>::New();
	cornerAnnotationA->SetLinearFontScaleFactor(2);
	cornerAnnotationA->SetNonlinearFontScaleFactor(1);
	cornerAnnotationA->SetMaximumFontSize(20);
	cornerAnnotationA->SetText(0, "Off Image");
	cornerAnnotationA->SetText(3, "<window>\n<level>");
	cornerAnnotationA->GetTextProperty()->SetColor(1, 0, 0);
	imageViewerA->GetRenderer()->AddViewProp(cornerAnnotationA);
	vtkSmartPointer<vtkImageInteractionCallbackA> callbackA =
		vtkSmartPointer<vtkImageInteractionCallbackA>::New();
	callbackA->SetViewer(imageViewerA);
	callbackA->SetAnnotation(cornerAnnotationA);
	callbackA->SetPicker(propPickerA);
	vtkInteractorStyleImage* imageStyleA = imageViewerA->GetInteractorStyle();
	imageStyleA->AddObserver(vtkCommand::MouseMoveEvent, callbackA);

	
	
	///====================================
	flagC = true;
	imageViewerC->SetInputConnection(threshould->GetOutputPort());
	imageViewerC->SetSliceOrientation(1);//修改参数为0，1，2可分别得到不同方向的切片

	imageViewerC->Render();
	imageViewerC->SetSlice(extent[3] / 2);
	ui->verticalScrollBar_C->setValue(extent[3] / 2);
	vtkSmartPointer<vtkPropPicker> propPickerC =
		vtkSmartPointer<vtkPropPicker>::New();
	propPickerC->PickFromListOn();
	propPickerC->AddPickList(imageViewerC->GetImageActor());
	vtkSmartPointer<vtkCornerAnnotation> cornerAnnotationC =
		vtkSmartPointer<vtkCornerAnnotation>::New();
	cornerAnnotationC->SetLinearFontScaleFactor(2);
	cornerAnnotationC->SetNonlinearFontScaleFactor(1);
	cornerAnnotationC->SetMaximumFontSize(20);
	cornerAnnotationC->SetText(0, "Off Image");
	cornerAnnotationC->SetText(3, "<window>\n<level>");
	cornerAnnotationC->GetTextProperty()->SetColor(1, 0, 0);
	imageViewerC->GetRenderer()->AddViewProp(cornerAnnotationC);
	vtkSmartPointer<vtkImageInteractionCallbackA> callbackC =
		vtkSmartPointer<vtkImageInteractionCallbackA>::New();
	callbackC->SetViewer(imageViewerC);
	callbackC->SetAnnotation(cornerAnnotationC);
	callbackC->SetPicker(propPickerC);
	vtkInteractorStyleImage* imageStyleC = imageViewerC->GetInteractorStyle();
	imageStyleC->AddObserver(vtkCommand::MouseMoveEvent, callbackC);
	//===========================================
	flagS = true;
	imageViewerS->SetInputConnection(threshould->GetOutputPort());
	imageViewerS->SetSliceOrientation(0);//修改参数为0，1，2可分别得到不同方向的切片

	imageViewerS->Render();
	imageViewerS->SetSlice(extent[1] / 2);
	ui->verticalScrollBar_S->setValue(extent[1] / 2);
	vtkSmartPointer<vtkPropPicker> propPickerS =
		vtkSmartPointer<vtkPropPicker>::New();
	propPickerS->PickFromListOn();
	propPickerS->AddPickList(imageViewerS->GetImageActor());
	vtkSmartPointer<vtkCornerAnnotation> cornerAnnotationS =
		vtkSmartPointer<vtkCornerAnnotation>::New();
	cornerAnnotationS->SetLinearFontScaleFactor(2);
	cornerAnnotationS->SetNonlinearFontScaleFactor(1);
	cornerAnnotationS->SetMaximumFontSize(20);
	cornerAnnotationS->SetText(0, "Off Image");
	cornerAnnotationS->SetText(3, "<window>\n<level>");
	cornerAnnotationS->GetTextProperty()->SetColor(1, 0, 0);
	imageViewerS->GetRenderer()->AddViewProp(cornerAnnotationS);
	vtkSmartPointer<vtkImageInteractionCallbackA> callbackS =
		vtkSmartPointer<vtkImageInteractionCallbackA>::New();
	callbackS->SetViewer(imageViewerS);
	callbackS->SetAnnotation(cornerAnnotationS);
	callbackS->SetPicker(propPickerS);
	vtkInteractorStyleImage* imageStyleS = imageViewerS->GetInteractorStyle();
	imageStyleS->AddObserver(vtkCommand::MouseMoveEvent, callbackS);
	irenA->Initialize();
	irenA->Start();
	irenC->Initialize();
	irenC->Start();
	irenS->Initialize();
	irenS->Start();
}
//更新断层图
void MainWindow::slotUpdateAxialSliceIndex(int a){
	if (flagA)
	{
		imageViewerA->SetSlice(a);
	}
}

void MainWindow::slotUpdateCornalSliceIndex(int a){
	if (flagC)
	{
		imageViewerC->SetSlice(a);
	}
}

void MainWindow::slotUpdateSagittalSliceIndex(int a){
	if (flagS)
	{
		imageViewerS->SetSlice(a);
	}
}

//阈值分割部分
void MainWindow::segmentBetween(){
	ui->textBrowser->setText("You could separate the lung by the threshold between -900 to -550 OR You could separate the skeleton by the threshold between 200 to 1000");
	int upperNum, lowerNum;
	QString upper, lower;
	upper = ui->textEdit_Up->document()->toPlainText();
	upperNum = upper.toInt();
	lower = ui->textEdit_Low->document()->toPlainText();
	lowerNum = lower.toInt();                         //从QTtextEdit中读取数据
	threshould->ThresholdBetween(lowerNum, upperNum);       // 利用ThresholdBetween进行分割
	threshould->SetInValue(1024);
	threshould->SetOutValue(-1024);

	threshould->Update(); //算法执行后更新

	slice();
	
}

//区域分割与中值滤波
void MainWindow::medianFilter(){
	int dims[3];
	int upperNum, upperNum2, upperNum3, upperNum4,upperNum5, upperNum6;
	QString upper, upper2, upper3, upper4,upper5, upper6;
	upper = ui->textEdit->document()->toPlainText();
	upperNum = upper.toInt();
	upper2 = ui->textEdit_2->document()->toPlainText();
	upperNum2 = upper2.toInt();
	upper3 = ui->textEdit_3->document()->toPlainText();
	upperNum3 = upper3.toInt();
	upper4 = ui->textEdit_4->document()->toPlainText();
	upperNum4 = upper4.toInt();
	upper5 = ui->textEdit_5->document()->toPlainText();
	upperNum5 = upper5.toInt();
	upper6 = ui->textEdit_6->document()->toPlainText();
	upperNum6 = upper6.toInt();
	reader->GetOutput()->GetDimensions(dims);

	for (int k = 0; k < dims[2]; k++)
	{
		for (int j = 0; j < dims[1]; j++)
		{
			for (int i = 0; i < dims[0]; i++)
			{

				short *pixel = (short *)(threshould->GetOutput()->GetScalarPointer(i, j, k));
				if (k < upperNum5 || k > upperNum6)
					*pixel = -1024;
				if (j < upperNum2 || j > upperNum4)
					*pixel = -1024;
				if (i < upperNum || i > upperNum3)
					*pixel = -1024;

				if ((j > 5) && (j < dims[1] - 6))
			   {
					short *pixel2 = (short *)(threshould->GetOutput()->GetScalarPointer(i, j + 5, k));
					short *pixel3 = (short *)(threshould->GetOutput()->GetScalarPointer(i, j - 5, k));
					if ((*pixel2 < -500) && (*pixel3 < -500))
						*pixel = -1024;
				}
			}

		}
	}
	threshould->Update();
	slice();                                   //区域分割后也同样更新阈值且再次slice

}

void MainWindow::DistanceB()
{
	vtkSmartPointer<vtkDistanceWidget> distanceWidgetA =
		vtkSmartPointer<vtkDistanceWidget>::New();
	distanceWidgetA->SetInteractor(irenA);
	distanceWidgetA->CreateDefaultRepresentation();
	static_cast<vtkDistanceRepresentation *>(distanceWidgetA->GetRepresentation())
		->SetLabelFormat("%-#6.3g");
	renWinA->Render();
	distanceWidgetA->On();
	vtkSmartPointer<vtkDistanceWidget> distanceWidgetC =
		vtkSmartPointer<vtkDistanceWidget>::New();
	distanceWidgetC->SetInteractor(irenC);
	distanceWidgetC->CreateDefaultRepresentation();
	static_cast<vtkDistanceRepresentation *>(distanceWidgetC->GetRepresentation())
		->SetLabelFormat("%-#6.3g");
	renWinC->Render();
	distanceWidgetC->On();
	vtkSmartPointer<vtkDistanceWidget> distanceWidgetS =
		vtkSmartPointer<vtkDistanceWidget>::New();
	distanceWidgetS->SetInteractor(irenS);
	distanceWidgetS->CreateDefaultRepresentation();
	static_cast<vtkDistanceRepresentation *>(distanceWidgetS->GetRepresentation())
		->SetLabelFormat("%-#6.3g");
	renWinS->Render();
	distanceWidgetS->On();

	irenA->Initialize();
	irenA->Start();
	irenC->Initialize();
	irenC->Start();
	irenS->Initialize();
	irenS->Start();
}
