
/*-------------------------------------sobel----------------------------------------------------------------------------*/

#include <vtkSmartPointer.h>

#include <vtkPNGReader.h>

#include <vtkImageSobel2D.h> //

#include <vtkImageExtractComponents.h> //vtkImageExtractComponents��ȡ��������ݶȷ���

#include <vtkImageMathematics.h> //�Ը�������ͼ��������ֵ

#include <vtkImageData.h>

#include <vtkImageShiftScale.h> //���ݷ�Χ������ֵ��Χ��0-255

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

	sobelFilter->SetInputConnection(reader->GetOutputPort());//��������������Ե



	//��ȡX���Ե�ɷ�

	vtkSmartPointer<vtkImageExtractComponents> xSobel = vtkSmartPointer<vtkImageExtractComponents>::New();

	xSobel->SetComponents(0);//��ȡ��һ�ɷּ�X���ݶ�

	xSobel->SetInputConnection(sobelFilter->GetOutputPort());

	xSobel->Update();



	vtkSmartPointer<vtkImageMathematics> absFilter = vtkSmartPointer<vtkImageMathematics>::New();

	//���ڼ���Sobel���ӵ�ֵ���ܴ��ڸ�ֵ���������vtkImageMathematics�Ը�������ͼ��������ֵ������vtkImageShiftScale��ͼ�����ֵ��Χ���ڵ�0-255֮������ʾ

	absFilter->SetOperationToAbsoluteValue();//����������Ϊ����ֵģʽ

	absFilter->SetInputConnection(xSobel->GetOutputPort());

	absFilter->Update();



	double xRange[2];

	absFilter->GetOutput()->GetScalarRange(xRange);



	vtkSmartPointer<vtkImageShiftScale> xShiftScale = vtkSmartPointer<vtkImageShiftScale>::New();

	xShiftScale->SetOutputScalarTypeToUnsignedChar();//ǿ������ת�� ������ʾ

	xShiftScale->SetScale(255 / xRange[1]);//��������

	xShiftScale->SetInputConnection(absFilter->GetOutputPort());

	xShiftScale->Update();



	//��ȡY���Ե�ɷ�

	vtkSmartPointer<vtkImageExtractComponents> ySobel = vtkSmartPointer<vtkImageExtractComponents>::New();

	ySobel->SetComponents(1);//��ȡ�ڶ��ɷּ�y���ݶ�

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


