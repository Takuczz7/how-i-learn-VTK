


#include <vtkSmartPointer.h>

#include <vtkRendererCollection.h>

#include <vtkPointPicker.h>

#include <vtkSphereSource.h>

#include <vtkPolyDataMapper.h>

#include <vtkRenderer.h>

#include <vtkRenderWindow.h>

#include <vtkRenderWindowInteractor.h>

#include <vtkActor.h>

#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkObjectFactory.h>

#include <vtkProperty.h>

#include <vtkSTLReader.h>

#include <vtkAutoInit.h> 

#include <iomanip> 

#include<cstdio>
#include "vtkDICOMImageReader.h"


// PointPickerInteractorStyle

class PointPickerInteractorStyle : public vtkInteractorStyleTrackballCamera

{

public:

	static PointPickerInteractorStyle* New();

	double picked[3];

	int pp2[2000][2];

	double pp[2000][3];

	long double value = 0;

	double value2 = 0;



	int i = 0, j = 0, x = 0, y = 0, x1 = 0, x2 = 0;

	vtkTypeMacro(PointPickerInteractorStyle, vtkInteractorStyleTrackballCamera);



	virtual void OnLeftButtonDown()

	{

		pp2[j][0] = this->Interactor->GetEventPosition()[0]; pp2[j][1] = this->Interactor->GetEventPosition()[1];

		std::cout << "Picking pixel: " << pp2[j][0] << " " << pp2[j][1] << std::endl;

		this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1],

			0,  // always zero.

			this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());



		this->Interactor->GetPicker()->GetPickPosition(picked);

		pp[i][0] = picked[0]; pp[i][1] = picked[1]; pp[i][2] = picked[2];

		std::cout << "Picked value: " << pp[i][0] << " " << pp[i][1] << " " << pp[i][2] << std::endl;

		if (j >= 1)

		{

			value2 = sqrt((pp2[j - 1][0] - pp2[j][0])*(pp2[j - 1][0] - pp2[j][0]) + (pp2[j - 1][1] - pp2[j][1])*(pp2[j - 1][1] - pp2[j][1]));

			std::cout << "两点之间的像素距离是： " << value2 << endl;

		}

		if (i >= 1)

		{

			value = sqrt((pp[i - 1][0] - pp[i][0]) * (pp[i - 1][0] - pp[i][0]) + (pp[i - 1][0] - pp[i][1]) * (pp[i - 1][1] - pp[i][1]) + (pp[i - 1][2] - pp[i][2])* (pp[i - 1][2] - pp[i][2]));

			std::cout << "世界坐标下的两点之间的距离是：" << value << endl;

		}

		i++; j++;

		vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();

		sphereSource->Update();

		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

		mapper->SetInputConnection(sphereSource->GetOutputPort());

		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

		actor->SetMapper(mapper);

		actor->SetPosition(picked);

		actor->SetScale(0.8);//设置显示点的大小

		actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

		this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);

		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();

	}

};

vtkStandardNewMacro(PointPickerInteractorStyle);



int main(int argc, char *argv[])

{
	if (argc < 2)
	{
		cout << "Usage: " << argv[0] << " file.mhd" << endl;
		return EXIT_FAILURE;
	}

	vtkSmartPointer<vtkDICOMImageReader> reader =
		vtkSmartPointer<vtkDICOMImageReader>::New();

	reader->SetDirectoryName(argv[1]);


	vtkSmartPointer<vtkPolyData> input = vtkSmartPointer<vtkPolyData>::New();



	reader->Update();

	

	// Create a mapper and actor

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	mapper->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

	actor->SetMapper(mapper);

	// Create a renderer, render window, and interactor

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

	renderWindow->Render();

	renderWindow->SetWindowName("PointPicker");

	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkPointPicker> pointPicker = vtkSmartPointer<vtkPointPicker>::New();

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	renderWindowInteractor->SetPicker(pointPicker);

	renderWindowInteractor->SetRenderWindow(renderWindow);

	vtkSmartPointer<PointPickerInteractorStyle> style = vtkSmartPointer<PointPickerInteractorStyle>::New();

	renderWindowInteractor->SetInteractorStyle(style);

	// Add the actor to the scene

	renderer->AddActor(actor);

	renderer->SetBackground(1, 1, 1);



	// Render and interact

	renderWindow->Render();

	renderWindowInteractor->Start();



	return EXIT_SUCCESS;

}

