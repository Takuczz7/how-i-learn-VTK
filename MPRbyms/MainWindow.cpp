#include "ui_MainWindow.h"
#include "MainWindow.h"


#include"vtkSmartPointer.h"
#include "vtkCommand.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include "vtkResliceImageViewer.h"
#include "vtkResliceCursorLineRepresentation.h"
#include "vtkResliceCursorThickLineRepresentation.h"
#include "vtkResliceCursorWidget.h"
#include "vtkResliceCursorActor.h"
#include "vtkResliceCursorPolyDataAlgorithm.h"
#include "vtkResliceCursor.h"
#include "vtkDICOMImageReader.h"
#include "vtkCellPicker.h"
#include "vtkProperty.h"
#include "vtkPlane.h"
#include "vtkImageData.h"
#include "vtkCommand.h"
#include "vtkPlaneSource.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "vtkInteractorStyleImage.h"
#include "vtkImageSlabReslice.h"
#include "vtkBoundedPlanePointPlacer.h"
#include "vtkDistanceWidget.h"
#include "vtkDistanceRepresentation.h"
#include "vtkHandleRepresentation.h"
#include "vtkResliceImageViewerMeasurements.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkPointHandleRepresentation3D.h"
#include "vtkPointHandleRepresentation2D.h"
#include "qfiledialog.h"
#include "vtkImageActor.h"
#include "vtkMatrix4x4.h"
#include "vtkImageMapper3D.h"
#include "vtkPropPicker.h"
#include"cmath"
#include "vtkTransform.h"

const double PI = 3.14159;
class vtkResliceCallback : public vtkCommand
{

	public:
		static vtkResliceCallback* New()
		{
			return new vtkResliceCallback;
		}
		vtkResliceCallback()
		{
			this->Translating = 0;
			this->ImageReslice = nullptr;
			this->Interactor = nullptr;
			this->Rotating = 0;
			this->Picker = 0;
			this->Viewer = 0;
			this->Renderer = 0;
			this->DistanceX = 0;
			this->DistanceY = 0;
			this->Actor = 0;
			this->Flag=0;
		}
		void SetFlag(int flag)
		{

			this->Flag = flag;
		}
		void SetImageActor(vtkImageActor*actor)
		{
			this->Actor = actor;
		}
		void SetDistanceX(double distanceX)
		{
			this->DistanceX = distanceX;
		}
		void SetDistanceY(double distanceY)
		{
			this->DistanceY = distanceY;
		}
		void SetRenderer(vtkRenderer*renderer)
		{
			this->Renderer = renderer;
		}
		void SetPicker(vtkPropPicker *picker)
		{
			this->Picker = picker;
		}

		void SetImageReslice(vtkImageReslice* reslice)
		{
			this->ImageReslice = reslice;
		}

		void SetMapToColors(vtkImageMapToColors* colors)
		{
			this->MapToColors = colors;
		}

		void SetInteractor(vtkRenderWindowInteractor* interactor)
		{
			this->Interactor = interactor;
		}

		void SetRenderWindow(vtkRenderWindow* window)
		{
			this->RenderWindow = window;
		}
		void SetViewer(vtkImageViewer2 *viewer)
		{
			this->Viewer = viewer;
		}

		void Execute(vtkObject* caller, unsigned long eventId, void* callData) override
		{
			int lastPos[2], curPos[2]; double pickPos[3];
			this->Picker->Pick(Interactor->GetEventPosition()[0], Interactor->GetEventPosition()[1], 0.0, Renderer);
			vtkAssemblyPath* path = this->Picker->GetPath();
			this->Picker->GetPickPosition(pickPos);
			this->Interactor->GetLastEventPosition(lastPos);
			this->Interactor->GetEventPosition(curPos);


			if (eventId==vtkCommand::MiddleButtonPressEvent)
			{
				this->Rotating = 1;
			}
			else if (eventId==vtkCommand::MiddleButtonReleaseEvent)
			{
				this->Rotating = 0;
			}
			if (eventId == vtkCommand::RightButtonPressEvent)
			{
				this->Translating = 1;
			}
			else if (eventId == vtkCommand::RightButtonReleaseEvent)
			{
				this->Translating = 0;
			}
			else if (eventId == vtkCommand::MouseMoveEvent)
			{
				if (this->Translating)
				{
					int deltaY = lastPos[1] - curPos[1];
					this->ImageReslice->Update();
					double spacing = this->ImageReslice->GetOutput()->GetSpacing()[2];
					vtkMatrix4x4* matrix = this->ImageReslice->GetResliceAxes();
					double point[4], center[4];
					point[0] = 0.0;
					point[1] = 0.0;
					point[2] = spacing * deltaY;
					point[3] = 1.0;

					matrix->MultiplyPoint(point, center);
					matrix->SetElement(0, 3, center[0]);
					matrix->SetElement(1, 3, center[1]);
					matrix->SetElement(2, 3, center[2]);

					this->MapToColors->Update();
					this->OutputImageData = this->MapToColors->GetOutput();

					this->Interactor->Render();
				}
				if (this->Rotating)
				{
					
					//double deltaY = lastPos[1] - pickPos[1];
					//double deltaX = lastPos[0] - pickPos[0];
					//std::cout << "x:" << pickPos[0] << "y:" << pickPos[1] << "z:" << pickPos[2] << std::endl;
					int deltaY = lastPos[1] - curPos[1];
					int deltaX = lastPos[0] - curPos[0];

					//std::cout << deltaX << std::endl;
					//std::cout << deltaY << std::endl;
					switch (Flag)
					{case 1:
						if (deltaX == 0)
						{

							auto trans = vtkSmartPointer<vtkTransform>::New();
							this->ImageReslice->Update();
							double spacing = this->ImageReslice->GetOutput()->GetSpacing()[1];
							double deltaYspacing = spacing * deltaY;
							vtkMatrix4x4* matrix = this->ImageReslice->GetResliceAxes();
							//std::cout <<* matrix << std::endl;
							trans->SetMatrix(matrix);
							double point[4];
							double Vcos; double Vsin; //double vcos;
							Vcos = cos(PI*deltaYspacing / 180);
							Vsin = sin(PI*deltaYspacing / 180);
							//point[0] = 1.0;
							//point[1] = cos;
							//point[2] = -sin;
							//point[3] = sin;
		/*					trans->RotateX(deltaYspacing);*/
							static double RotateX[16] = {
								1, 0, 0, 0,
								0, Vcos, -Vsin, 0,
								0, Vsin, Vcos, 0,
								0, 0, 0, 1 };
							auto RotateXAixs = vtkSmartPointer<vtkMatrix4x4>::New();
							RotateXAixs->DeepCopy(RotateX);
							//std::cout << *RotateXAixs << std::endl;
							//trans->PostMultiply();
							//trans->GetMatrix->MultiplyPoint(RotateXAixs, matrix);
							//matrix->SetElement(0, 0, point[0]);
							//matrix->SetElement(3, 3, point[0]);
							//matrix->SetElement(1, 1, point[1]);
							//matrix->SetElement(2, 2, point[1]);
							//matrix->SetElement(1, 2, point[2]);
							//matrix->SetElement(2, 1, point[3]);
							//auto matrixdata = vtkSmartPointer<vtkMatrix4x4>::New();
							auto matrixstore = vtkSmartPointer<vtkMatrix4x4>::New();
							/*for (int j = 0; j < 4; j++)
							{
							for (int i = 0; i < 4;i++)
							{
							matrixdata->SetElement(i, j, matrix->GetElement(i, j));
							}
							}
							std::cout << *matrixdata << std::endl;*/
							matrix->Multiply4x4(RotateXAixs, matrix, matrixstore);
						/*	matrix->DeepCopy(RotateX);*/
							/*for (int j = 0; j < 4; j++)
							{
							for (int i = 0; i < 4; i++)
							{
							matrix->SetElement(i, j, matrixstore->GetElement(i, j));
							}
							}*/
							//std::cout << *matrix << std::endl;
							//vcos=180*acos(Vcos)/PI;
							//this->Actor->RotateX(vcos);
							matrix->DeepCopy(matrixstore);
							this->MapToColors->Update();
							this->OutputImageData = this->MapToColors->GetOutput();

							//this->Actor->Update();
							this->Interactor->Render();
						}

						if (deltaY == 0)
						{
							auto trans = vtkSmartPointer<vtkTransform>::New();
							this->ImageReslice->Update();
							double spacing = this->ImageReslice->GetOutput()->GetSpacing()[0];
							double deltaXspacing = spacing * deltaX;
							vtkMatrix4x4* matrix = this->ImageReslice->GetResliceAxes();
							//std::cout << matrix << std::endl;
							double point[4];
							double Vcos; double Vsin; //double vcos;
							Vcos = cos(PI*deltaXspacing / 180);
							Vsin = sin(PI*deltaXspacing / 180);
							//trans->SetMatrix(matrix);
							//trans->RotateY(deltaXspacing);
							//point[0] = 1.0;
							//point[1] = Vcos;
							//point[2] = -Vsin;
							//point[3] = Vsin;
							//matrix->SetElement(1, 1, point[0]);
							//matrix->SetElement(3, 3, point[0]);
							//matrix->SetElement(0, 0, point[1]);
							//matrix->SetElement(2, 2, point[1]);
							//matrix->SetElement(2, 0, point[2]);
							//matrix->SetElement(0, 2, point[3]);
							static double RotateY[16] = {
								Vcos, 0, Vsin, 0,
								0, 1, 0, 0,
								-Vsin, 0, Vcos, 0,
								0, 0, 0, 1 };

							auto RotateYAixs = vtkSmartPointer<vtkMatrix4x4>::New();
							RotateYAixs->DeepCopy(RotateY);
							/*				trans->PostMultiply();
							trans->GetMatrix->MultiplyPoint(RotateYAixs, matrix);*/
							//auto matrixdata = vtkSmartPointer<vtkMatrix4x4>::New();
							auto matrixstore = vtkSmartPointer<vtkMatrix4x4>::New();
							/*					for (int j = 0; j < 4; j++)
							{
							for (int i = 0; i < 4; i++)
							{
							matrixdata->SetElement(i, j, matrix->GetElement(i, j));
							}
							}*/
							matrix->Multiply4x4(RotateYAixs, matrix, matrixstore);
							matrix->DeepCopy(matrixstore);
							/*for (int j = 0; j < 4; j++)
							{
							for (int i = 0; i < 4; i++)
							{
							matrix->SetElement(i, j, matrixstore->GetElement(i, j));
							}
							}
							std::cout << matrix << std::endl;*/
							//	vcos = 180 * acos(Vcos) / PI;
							//std::cout << vcos << std::endl;
							//	this->Actor->RotateY(vcos);
							this->MapToColors->Update();
							this->OutputImageData = this->MapToColors->GetOutput();
							//	this->Actor->Update();
							this->Interactor->Render();
						}

					case 2:
					case 3:

					default:
						break;
					}
				

				}

				else
				{
					vtkInteractorStyle* style = vtkInteractorStyle::SafeDownCast(
						this->Interactor->GetInteractorStyle());
					if (style)
					{
						style->OnMouseMove();
					}
				}
			}
		}

	private:
		int Translating; int Rotating;
		vtkImageReslice* ImageReslice;
		vtkImageMapToColors* MapToColors;
		vtkRenderWindowInteractor* Interactor;
		vtkRenderWindow* RenderWindow;
		vtkImageData* OutputImageData;
		vtkPropPicker *Picker;
		vtkImageViewer2 *Viewer;
		vtkRenderer*Renderer;
		vtkImageActor*Actor;
		double DistanceX;double DistanceY;
		int Flag;
};




MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{

	this->ui->setupUi(this);

	connect(ui->pushButton_Read, SIGNAL(clicked()), this, SLOT(on_BtnExp_clicked()));
	connect(ui->pushButton_Reset, SIGNAL(clicked()), this, SLOT(ResetViews()));
	connect(ui->checkBox_2, SIGNAL(stateChanged(int)), this, SLOT(reslice(int)));


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
void MainWindow::on_BtnExp_clicked()
{
	QString myPath = GetFileDirDLG();
	// 读取显示
	reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetDirectoryName(myPath.toStdString().c_str());
	reader->Update();
	int dims[3];
	reader->GetOutput()->GetDimensions(dims);
//------------------------------------------------------------------------------------------	
	//riw[0] = vtkSmartPointer<vtkResliceImageViewer>::New();
	//riw[1] = vtkSmartPointer<vtkResliceImageViewer>::New();
	//riw[2] = vtkSmartPointer<vtkResliceImageViewer>::New();
	//this->ui->qvtkWidget->SetRenderWindow(riw[0]->GetRenderWindow());
	//riw[0]->SetupInteractor(this->ui->qvtkWidget->GetRenderWindow()->GetInteractor());
	//this->ui->qvtkWidget_2->SetRenderWindow(riw[1]->GetRenderWindow());
	//riw[1]->SetupInteractor(this->ui->qvtkWidget_2->GetRenderWindow()->GetInteractor());
	//this->ui->qvtkWidget_3->SetRenderWindow(riw[2]->GetRenderWindow());
	//riw[2]->SetupInteractor(this->ui->qvtkWidget_3->GetRenderWindow()->GetInteractor());
	////所有窗口统一
	//for (int i = 0; i < 3; i++)
	//{
	//vtkResliceCursorLineRepresentation *rep =
	//vtkResliceCursorLineRepresentation::SafeDownCast(riw[i]->GetResliceCursorWidget()->GetRepresentation());
	//	riw[i]->SetResliceCursor(riw[0]->GetResliceCursor());
	//	rep->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(i);
	//	riw[i]->SetInputData(reader->GetOutput());
	//	riw[i]->SetSliceOrientation(i);
	//	riw[i]->SetResliceModeToAxisAligned();
	//}
	//
	//vtkSmartPointer<vtkCellPicker> picker =
	//	vtkSmartPointer<vtkCellPicker>::New();
	//picker->SetTolerance(0.005);
	//vtkSmartPointer<vtkProperty> ipwProp =
	//	vtkSmartPointer<vtkProperty>::New();
	//vtkSmartPointer< vtkRenderer > ren =
	//	vtkSmartPointer< vtkRenderer >::New();
	//this->ui->qvtkWidget_4->GetRenderWindow()->AddRenderer(ren);
	//vtkRenderWindowInteractor *iren = this->ui->qvtkWidget_4->GetInteractor();
	//
	//for (int i = 0; i < 3; i++)
	//{
	//	planeWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();
	//	planeWidget[i]->SetInteractor(iren);
	//	planeWidget[i]->SetPicker(picker);
	//	planeWidget[i]->RestrictPlaneToVolumeOn();
	//	double color[3] = { 0, 0, 0 };
	//	color[i] = 1;
	//	planeWidget[i]->GetPlaneProperty()->SetColor(color);
	//	color[0] /= 4.0;
	//	color[1] /= 4.0;
	//	color[2] /= 4.0;
	//	riw[i]->GetRenderer()->SetBackground(color);
	//	planeWidget[i]->SetTexturePlaneProperty(ipwProp);
	//	planeWidget[i]->TextureInterpolateOff();
	//	planeWidget[i]->SetResliceInterpolateToLinear();
	//	planeWidget[i]->SetInputConnection(reader->GetOutputPort());
	//	planeWidget[i]->SetPlaneOrientation(i);
	//	planeWidget[i]->SetSliceIndex(dims[i] / 2);
	//	planeWidget[i]->DisplayTextOn();
	//	planeWidget[i]->SetDefaultRenderer(ren);
	//	planeWidget[i]->SetWindowLevel(1358, -27);
	//	planeWidget[i]->On();
	//	planeWidget[i]->InteractionOn();
	//}
	//this->ui->qvtkWidget->show();
	//this->ui->qvtkWidget_2->show();
	//this->ui->qvtkWidget_3->show();

	int extent[6];
	double spacing[3];
	double origin[3];
	double center[3];

	reader->GetOutput()->GetExtent(extent);
	reader->GetOutput()->GetSpacing(spacing);
	reader->GetOutput()->GetOrigin(origin);

	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

	static double sagittalElements[16] = {
		0, 0, -1, 0,
		1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, 0, 1 };

	static double cornalElements[16] = {
		1, 0, 0, 0,
		0, 0, 1, 0,
		0, -1, 0, 0,
		0, 0, 0, 1 };

	static double axialElements[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };


	auto resliceAxes_C = vtkSmartPointer<vtkMatrix4x4>::New();
	resliceAxes_C->DeepCopy(cornalElements);
	resliceAxes_C->SetElement(0, 3, center[0]);
	resliceAxes_C->SetElement(1, 3, center[1]);
	resliceAxes_C->SetElement(2, 3, center[2]);

	auto resliceAxes_S = vtkSmartPointer<vtkMatrix4x4>::New();
	resliceAxes_S->DeepCopy(sagittalElements);
	resliceAxes_S->SetElement(0, 3, center[0]);
	resliceAxes_S->SetElement(1, 3, center[1]);
	resliceAxes_S->SetElement(2, 3, center[2]);

	auto resliceAxes_A = vtkSmartPointer<vtkMatrix4x4>::New();
	resliceAxes_A->DeepCopy(axialElements);
	resliceAxes_A->SetElement(0, 3, center[0]);
	resliceAxes_A->SetElement(1, 3, center[1]);
	resliceAxes_A->SetElement(2, 3, center[2]);

//-----------------------------------------------------------------------------
	double distanceAX, distanceAY, distanceCX, distanceCY, distanceSX, distanceSY;

	distanceAX = 0.5*spacing[0] * (extent[0] + extent[1]);
	distanceAY = 0.5*spacing[2] * (extent[4] + extent[5]);
	distanceCX = 0.5*spacing[0] * (extent[0] + extent[1]);
	distanceCY = 0.5*spacing[1] * (extent[2] + extent[3]);
	distanceSX = 0.5*spacing[2] * (extent[4] + extent[5]);
	distanceSY = 0.5*spacing[1] * (extent[2] + extent[3]);
		


	auto ImageReslice_C = vtkSmartPointer<vtkImageReslice>::New();
	ImageReslice_C->SetInputConnection(reader->GetOutputPort());
	ImageReslice_C->SetOutputDimensionality(2);
	ImageReslice_C->SetResliceAxes(resliceAxes_C);
	ImageReslice_C->SetResliceAxesOrigin(center);
	ImageReslice_C->SetInterpolationModeToLinear();


	
	auto ImageReslice_S = vtkSmartPointer<vtkImageReslice>::New();
	ImageReslice_S->SetInputConnection(reader->GetOutputPort());
	ImageReslice_S->SetOutputDimensionality(2);
	ImageReslice_S->SetResliceAxes(resliceAxes_S);
	ImageReslice_S->SetResliceAxesOrigin(center);
	ImageReslice_S->SetInterpolationModeToLinear();

	auto ImageReslice_A = vtkSmartPointer<vtkImageReslice>::New();
	ImageReslice_A->SetInputConnection(reader->GetOutputPort());
	ImageReslice_A->SetOutputDimensionality(2);
	ImageReslice_A->SetResliceAxes(resliceAxes_A);
	ImageReslice_A->SetResliceAxesOrigin(center);
	ImageReslice_A->SetInterpolationModeToLinear();


	auto lookupTable = vtkSmartPointer<vtkLookupTable>::New();
	lookupTable->SetRange(-2000, 2000);
	lookupTable->SetValueRange(0.0, 1.0);
	lookupTable->SetSaturationRange(0.0, 0.0);
	lookupTable->SetRampToLinear();
	lookupTable->Build();

	auto mapToColors_C = vtkSmartPointer<vtkImageMapToColors>::New();
	auto mapToColors_A = vtkSmartPointer<vtkImageMapToColors>::New();
	auto mapToColors_S = vtkSmartPointer<vtkImageMapToColors>::New();
	mapToColors_C->SetLookupTable(lookupTable);
	mapToColors_S->SetLookupTable(lookupTable);
	mapToColors_A->SetLookupTable(lookupTable);
	mapToColors_C->SetInputConnection(ImageReslice_C->GetOutputPort());
	mapToColors_S->SetInputConnection(ImageReslice_S->GetOutputPort());
	mapToColors_A->SetInputConnection(ImageReslice_A->GetOutputPort());
	mapToColors_C->Update();
	mapToColors_S->Update();
	mapToColors_A->Update();

	auto imageActor_A = vtkSmartPointer<vtkImageActor>::New();
	imageActor_A->GetMapper()->SetInputConnection(mapToColors_A->GetOutputPort());
	auto imageActor_S = vtkSmartPointer<vtkImageActor>::New();
	imageActor_S->GetMapper()->SetInputConnection(mapToColors_S->GetOutputPort());
	auto imageActor_C = vtkSmartPointer<vtkImageActor>::New();
	imageActor_C->GetMapper()->SetInputConnection(mapToColors_C->GetOutputPort());
	
	vtkSmartPointer<vtkPropPicker> propPickerA =
		vtkSmartPointer<vtkPropPicker>::New();
	propPickerA->PickFromListOn();
	propPickerA->AddPickList(imageActor_A);
	vtkSmartPointer<vtkPropPicker> propPickerC =
		vtkSmartPointer<vtkPropPicker>::New();
	propPickerC->PickFromListOn();
	propPickerC->AddPickList(imageActor_C);
	vtkSmartPointer<vtkPropPicker> propPickerS =
		vtkSmartPointer<vtkPropPicker>::New();
	propPickerS->PickFromListOn();
	propPickerS->AddPickList(imageActor_S);

	auto aRendererC = vtkSmartPointer<vtkRenderer>::New();
	aRendererC->AddActor(imageActor_C);
	auto renWinC = vtkSmartPointer<vtkRenderWindow>::New();
	renWinC = ui->qvtkWidget->GetRenderWindow();
	renWinC->AddRenderer(aRendererC);
	auto imageStyle_C = vtkSmartPointer<vtkInteractorStyleImage>::New();
	auto irenC = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	irenC->SetInteractorStyle(imageStyle_C);
	irenC->SetRenderWindow(renWinC);

	auto aRendererA = vtkSmartPointer<vtkRenderer>::New();
	aRendererA->AddActor(imageActor_A);
	auto renWinA = vtkSmartPointer<vtkRenderWindow>::New();
	renWinA = ui->qvtkWidget_3->GetRenderWindow();
	renWinA->AddRenderer(aRendererA);
	auto imageStyle_A = vtkSmartPointer<vtkInteractorStyleImage>::New();
	auto irenA = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	irenA->SetInteractorStyle(imageStyle_A);
	irenA->SetRenderWindow(renWinA);

	auto aRendererS = vtkSmartPointer<vtkRenderer>::New();
	aRendererS->AddActor(imageActor_S);
	auto renWinS = vtkSmartPointer<vtkRenderWindow>::New();
		renWinS = ui->qvtkWidget_2->GetRenderWindow();
	renWinS->AddRenderer(aRendererS);
	auto imageStyle_S = vtkSmartPointer<vtkInteractorStyleImage>::New();
	auto irenS = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	irenS->SetInteractorStyle(imageStyle_S);
	irenS->SetRenderWindow(renWinS);

	int flagA= 1;
	int flagC=2;
	int flagS = 3;

	//auto aRenderer = vtkSmartPointer<vtkRenderer>::New();
	//aRenderer->AddActor(imageActor_S);
	//aRenderer->AddActor(imageActor_C);
	//aRenderer->AddActor(imageActor_A);
	//auto renWin = vtkSmartPointer<vtkRenderWindow>::New();
	//renWin->AddRenderer(aRenderer);
	//auto imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
	//auto iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	//iren->SetInteractorStyle(imageStyle);
	//iren->SetRenderWindow(renWin);
	
	//renWinA = ui->qvtkWidget_3->GetRenderWindow();
	//renWinS = ui->qvtkWidget_2->GetRenderWindow();
	//renWinC = ui->qvtkWidget->GetRenderWindow();
	//renWin = ui->qvtkWidget_4->GetRenderWindow();
	//ui->qvtkWidget->GetRenderWindow()->AddRenderer(aRendererC);
	//ui->qvtkWidget_2->GetRenderWindow()->AddRenderer(aRendererS);
	//ui->qvtkWidget_3->GetRenderWindow()->AddRenderer(aRendererA);
	//ui->qvtkWidget_4->GetRenderWindow()->AddRenderer(aRenderer);
	//ui->qvtkWidget->GetRenderWindow()->Render();
	//ui->qvtkWidget_2->GetRenderWindow()->Render();
	//ui->qvtkWidget_3->GetRenderWindow()->Render();

	irenA->Initialize();
	irenS->Initialize();
	irenC->Initialize();
	//iren->Initialize();


	auto callbackA = vtkSmartPointer<vtkResliceCallback>::New();
	callbackA->SetImageReslice(ImageReslice_A);
	callbackA->SetMapToColors(mapToColors_A);
	callbackA->SetInteractor(irenA);
	callbackA->SetRenderWindow(renWinA);
	callbackA->SetRenderer(aRendererA);
	callbackA->SetPicker(propPickerA);
	callbackA->SetDistanceX(distanceAX);
	callbackA->SetDistanceY(distanceAY);
	callbackA->SetImageActor(imageActor_A);
	callbackA->SetFlag(flagA);
	imageStyle_A->AddObserver(vtkCommand::RightButtonPressEvent, callbackA);
	imageStyle_A->AddObserver(vtkCommand::RightButtonReleaseEvent, callbackA);
	imageStyle_A->AddObserver(vtkCommand::MouseMoveEvent, callbackA);
	imageStyle_A->AddObserver(vtkCommand::MiddleButtonPressEvent, callbackA);
	imageStyle_A->AddObserver(vtkCommand::MiddleButtonReleaseEvent, callbackA);

	auto callbackC = vtkSmartPointer<vtkResliceCallback>::New();
	callbackC->SetImageReslice(ImageReslice_C);
	callbackC->SetMapToColors(mapToColors_C);
	callbackC->SetInteractor(irenC);
	callbackC->SetRenderWindow(renWinC);
	callbackC->SetRenderer(aRendererC);
	callbackC->SetPicker(propPickerC);
	callbackC->SetDistanceX(distanceCX);
	callbackC->SetDistanceY(distanceCY);
	callbackC->SetImageActor(imageActor_C);
	callbackC->SetFlag(flagC);
	imageStyle_C->AddObserver(vtkCommand::RightButtonPressEvent, callbackC);
	imageStyle_C->AddObserver(vtkCommand::RightButtonReleaseEvent, callbackC);
	imageStyle_C->AddObserver(vtkCommand::MouseMoveEvent, callbackC);
	imageStyle_C->AddObserver(vtkCommand::MiddleButtonPressEvent, callbackC);
	imageStyle_C->AddObserver(vtkCommand::MiddleButtonReleaseEvent, callbackC);

	auto callbackS = vtkSmartPointer<vtkResliceCallback>::New();
	callbackS->SetImageReslice(ImageReslice_S);
	callbackS->SetMapToColors(mapToColors_S);
	callbackS->SetInteractor(irenS);
	callbackS->SetRenderWindow(renWinS);
	callbackS->SetRenderer(aRendererS);
	callbackS->SetPicker(propPickerS);
	callbackS->SetDistanceX(distanceSX);
	callbackS->SetDistanceY(distanceSY);
	callbackS->SetImageActor(imageActor_S);
	callbackS->SetFlag(flagS);
	imageStyle_S->AddObserver(vtkCommand::RightButtonPressEvent, callbackS);
	imageStyle_S->AddObserver(vtkCommand::RightButtonReleaseEvent, callbackS);
	imageStyle_S->AddObserver(vtkCommand::MouseMoveEvent, callbackS);
	imageStyle_S->AddObserver(vtkCommand::MiddleButtonReleaseEvent, callbackS);
	imageStyle_S->AddObserver(vtkCommand::MiddleButtonPressEvent, callbackS);


	irenA->Start();
	irenS->Start();
	irenC->Start();
	/*iren->Start();*/

}

void MainWindow::ResetViews()
{
	//// Reset the reslice image views
	//for (int i = 0; i < 3; i++)
	//{
	//	riw[i]->Reset();
	//}
	//// Also sync the Image plane widget on the 3D top right view with any
	//// changes to the reslice cursor.
	//for (int i = 0; i < 3; i++)
	//{
	//	vtkPlaneSource *ps = static_cast<vtkPlaneSource *>(
	//		planeWidget[i]->GetPolyDataAlgorithm());
	//	ps->SetNormal(riw[0]->GetResliceCursor()->GetPlane(i)->GetNormal());
	//	ps->SetCenter(riw[0]->GetResliceCursor()->GetPlane(i)->GetOrigin());
	//	// If the reslice plane has modified, update it on the 3D widget
	//	this->planeWidget[i]->UpdatePlacement();
	//}
	//// Render in response to changes.
	//this->Render();


}

void MainWindow::Render()
{
	//for (int i = 0; i < 3; i++)
	//{
	//	riw[i]->Render();
	//}
	//this->ui->qvtkWidget_3->GetRenderWindow()->Render();

}

void MainWindow::reslice(int mode)
{
	/*ui->checkBox_2->setEnabled(mode ? 1: 0);
	if (mode)
	{
	for (int i = 0; i < 3; i++)
	{
	riw[i]->SetResliceMode(mode ? 1 : 0);
	riw[i]->GetRenderer()->ResetCamera();
	riw[i]->Render();
	}

	*/

	}



