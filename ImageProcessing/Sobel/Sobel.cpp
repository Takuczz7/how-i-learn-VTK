
/*-------------------------------------sobel----------------------------------------------------------------------------*/

#include <vtkSmartPointer.h>

#include <vtkPNGReader.h>

#include <vtkImageSobel2D.h> //

#include <vtkImageExtractComponents.h> //vtkImageExtractComponents提取各方向的梯度分量

#include <vtkImageMathematics.h> //对各个分量图像计算绝对值

#include <vtkImageData.h>

#include <vtkImageShiftScale.h> //数据范围调整数值范围到0-255

#include <vtkImageActor.h>

#include <vtkRenderer.h>

#include <vtkRenderWindow.h>

#include <vtkRenderWindowInteractor.h>

#include <vtkInteractorStyleImage.h>



int main()

{

	vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();

	reader->SetFileName("F:\\czz\\vtkBuild\\Examples\\ImageProcessing\\Sobel\\Lena.png");

	reader->Update();



	vtkSmartPointer<vtkImageSobel2D> sobelFilter = vtkSmartPointer<vtkImageSobel2D>::New();

	sobelFilter->SetInputConnection(reader->GetOutputPort());//包含横向和竖向边缘



	//提取X向边缘成分

	vtkSmartPointer<vtkImageExtractComponents> xSobel = vtkSmartPointer<vtkImageExtractComponents>::New();

	xSobel->SetComponents(0);//提取第一成分即X向梯度

	xSobel->SetInputConnection(sobelFilter->GetOutputPort());

	xSobel->Update();



	vtkSmartPointer<vtkImageMathematics> absFilter = vtkSmartPointer<vtkImageMathematics>::New();

	//由于计算Sobel算子的值可能存在负值，因此利用vtkImageMathematics对各个分量图像计算绝对值，再由vtkImageShiftScale将图像的数值范围调节到0-255之间再显示

	absFilter->SetOperationToAbsoluteValue();//将属性设置为绝对值模式

	absFilter->SetInputConnection(xSobel->GetOutputPort());

	absFilter->Update();



	double xRange[2];

	absFilter->GetOutput()->GetScalarRange(xRange);



	vtkSmartPointer<vtkImageShiftScale> xShiftScale = vtkSmartPointer<vtkImageShiftScale>::New();

	xShiftScale->SetOutputScalarTypeToUnsignedChar();//强制类型转换 方便显示

	xShiftScale->SetScale(255 / xRange[1]);//设置属性

	xShiftScale->SetInputConnection(absFilter->GetOutputPort());

	xShiftScale->Update();



	//提取Y向边缘成分

	vtkSmartPointer<vtkImageExtractComponents> ySobel = vtkSmartPointer<vtkImageExtractComponents>::New();

	ySobel->SetComponents(1);//提取第二成分即y向梯度

	ySobel->SetInputConnection(sobelFilter->GetOutputPort());

	ySobel->Update();



	vtkSmartPointer<vtkImageMathematics> absYsobel = vtkSmartPointer<vtkImageMathematics>::New();

	absYsobel->SetOperationToAbsoluteValue();

	absYsobel->SetInputConnection(ySobel->GetOutputPort());

	absYsobel->Update();



	double yRange[2];

	absYsobel->GetOutput()->GetScalarRange(yRange);



	vtkSmartPointer<vtkImageShiftScale> yShiftScale = vtkSmartPointer<vtkImageShiftScale>::New();

	yShiftScale->SetOutputScalarTypeToUnsignedChar();

	yShiftScale->SetScale(255 / yRange[1]);

	yShiftScale->SetInputConnection(absYsobel->GetOutputPort());

	yShiftScale->Update();

	////////////////////////////////////////////////////////////

	vtkSmartPointer<vtkImageActor> origActor = vtkSmartPointer<vtkImageActor>::New();

	origActor->SetInputData(reader->GetOutput());



	vtkSmartPointer<vtkImageActor> xSobelActor = vtkSmartPointer<vtkImageActor>::New();

	xSobelActor->SetInputData(xShiftScale->GetOutput());



	vtkSmartPointer<vtkImageActor> ySobelActor = vtkSmartPointer<vtkImageActor>::New();

	ySobelActor->SetInputData(yShiftScale->GetOutput());

	/////////////////////////////////////////////////////////////

	double origView[4] = { 0, 0, 0.33, 1 };

	double xSobelView[4] = { 0.33, 0, 0.66, 1 };

	double ySobelView[4] = { 0.66, 0, 1, 1 };

	vtkSmartPointer<vtkRenderer> origRender = vtkSmartPointer<vtkRenderer>::New();

	origRender->SetViewport(origView);

	origRender->AddActor(origActor);

	origRender->ResetCamera();

	origRender->SetBackground(1, 1, 1);



	vtkSmartPointer<vtkRenderer> xSobelRender = vtkSmartPointer<vtkRenderer>::New();

	xSobelRender->SetViewport(xSobelView);

	xSobelRender->AddActor(xSobelActor);

	xSobelRender->ResetCamera();

	xSobelRender->SetBackground(1, 1, 1);



	vtkSmartPointer<vtkRenderer> ySobelRender = vtkSmartPointer<vtkRenderer>::New();

	ySobelRender->SetViewport(ySobelView);

	ySobelRender->AddActor(ySobelActor);

	ySobelRender->ResetCamera();

	ySobelRender->SetBackground(1, 1, 1);

	//////////////////////////////////////////////

	vtkSmartPointer<vtkRenderWindow> rw = vtkSmartPointer<vtkRenderWindow>::New();

	rw->AddRenderer(origRender);

	rw->AddRenderer(xSobelRender);

	rw->AddRenderer(ySobelRender);

	rw->SetSize(960, 320);

	rw->SetWindowName("Edge by Soebl");



	vtkSmartPointer<vtkRenderWindowInteractor> rwi = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

	rwi->SetInteractorStyle(style);

	rwi->SetRenderWindow(rw);

	rwi->Initialize();

	rwi->Start();



	return 0;

}


