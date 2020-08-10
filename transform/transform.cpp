
#include <vtkLineSource.h>

#include <vtkPolyData.h>

#include <vtkSmartPointer.h>

#include <vtkPolyDataMapper.h>

#include <vtkActor.h>

#include <vtkRenderWindow.h>

#include <vtkRenderer.h>

#include <vtkRenderWindowInteractor.h>

#include <vtkProperty.h>

#include <vtkAxesActor.h>

#include <vtkConeSource.h>

#include <vtkTextActor.h>

#include <vtkTextProperty.h>

#include <vtkTransform.h>

#include <vtkSphereSource.h>



int main(int, char *[])

{

	vtkSmartPointer<vtkSphereSource> sphereSource =

		vtkSmartPointer<vtkSphereSource>::New();

	sphereSource->SetRadius(0.1);

	sphereSource->Update();



	vtkSmartPointer<vtkPolyDataMapper> sphereMapper =

		vtkSmartPointer<vtkPolyDataMapper>::New();

	sphereMapper->SetInputConnection(sphereSource->GetOutputPort());



	vtkSmartPointer<vtkActor> sphereActor =

		vtkSmartPointer<vtkActor>::New();

	sphereActor->SetPosition(0, 0, 0);

	sphereActor->SetMapper(sphereMapper);

	sphereActor->GetProperty()->SetColor(1, 0, 0);



	vtkSmartPointer<vtkConeSource> coneSource =

		vtkSmartPointer<vtkConeSource>::New();

	coneSource->SetRadius(.2);

	coneSource->SetHeight(.5);

	coneSource->SetCenter(0, 0, 0);

	vtkSmartPointer<vtkPolyDataMapper> coneMapper =

		vtkSmartPointer<vtkPolyDataMapper>::New();

	coneMapper->SetInputConnection(coneSource->GetOutputPort());

	vtkSmartPointer<vtkActor> coneActor =

		vtkSmartPointer<vtkActor>::New();

	coneActor->SetMapper(coneMapper);



	vtkSmartPointer<vtkActor> oriConeActor =

		vtkSmartPointer<vtkActor>::New();

	oriConeActor->SetMapper(coneMapper);

#define AXIS_LEN 1.

	vtkSmartPointer<vtkAxesActor> oriAxesActor =

		vtkSmartPointer<vtkAxesActor>::New();

	oriAxesActor->SetPosition(0, 0, 0);

	oriAxesActor->SetTotalLength(AXIS_LEN, AXIS_LEN, AXIS_LEN);

	oriAxesActor->SetShaftType(0);

	oriAxesActor->SetAxisLabels(0);

	oriAxesActor->SetCylinderRadius(0.02);



	vtkSmartPointer<vtkAxesActor> axesActor =

		vtkSmartPointer<vtkAxesActor>::New();

	axesActor->SetPosition(0, 0, 0);

	axesActor->SetTotalLength(AXIS_LEN, AXIS_LEN, AXIS_LEN);

	axesActor->SetShaftType(0);

	axesActor->SetAxisLabels(0);

	axesActor->SetCylinderRadius(0.02);



	vtkSmartPointer<vtkTextActor> textActor =

		vtkSmartPointer<vtkTextActor>::New();

	textActor->SetPosition2(100, 40);

	textActor->GetTextProperty()->SetFontSize(24);

	textActor->GetTextProperty()->SetColor(1, 0, 0);





	vtkSmartPointer<vtkTransform> trans =

		vtkSmartPointer<vtkTransform>::New();



#if 0

	trans->PostMultiply();



	coneActor->SetPosition(1, 0, 0);

	//trans->Translate(1, 0, 0);

	//trans->RotateZ(45);

	trans->RotateZ(45);

	trans->Translate(1, 0, 0);

	coneActor->SetUserTransform(trans);

	//textActor->SetInput("PostMultiply()\nTranslate(1, 0, 0)\nRotateZ(45)");

	textActor->SetInput("PostMultiply()\nRotateZ(45)\nTranslate(1, 0, 0)");

#endif



#if 1

	//coneActor->RotateZ(45);

	//coneActor->SetPosition(1, 0, 0);

	//textActor->SetInput("coneActor->RotateZ(45)\nconeActor->SetPosition(1, 0, 0)");



	trans->RotateZ(45);

	trans->Translate(1, 0, 0);

	coneActor->SetUserTransform(trans);

	textActor->SetInput("trans->RotateZ(45)\ntrans->Translate(1, 0, 0)\nconeActor->SetUserTransform(trans)");



	cout << "GetMatrix:" << endl;

	if (coneActor->GetMatrix() != NULL)

	{

		coneActor->GetMatrix()->Print(cout);

	}

	else

	{

		cout << "NULL" << endl;

	}

	cout << "GetUserMatrix:" << endl;

	if (coneActor->GetUserMatrix() != NULL)

	{

		coneActor->GetUserMatrix()->Print(cout);

	}

	else

	{

		cout << "NULL" << endl;

	}

	//cout << "GetUserTransform:" << endl;

	//if (coneActor->GetUserTransform() !=NULL)

	//{

	//	coneActor->GetUserTransform()->Print(cout);

	//}

	//else

	//{

	//	cout << "NULL" << endl;

	//}

#endif

	vtkSmartPointer<vtkRenderer> renderer1 =

		vtkSmartPointer<vtkRenderer>::New();

	vtkSmartPointer<vtkRenderer> renderer2 =

		vtkSmartPointer<vtkRenderer>::New();



	vtkSmartPointer<vtkRenderWindow> renderWindow =

		vtkSmartPointer<vtkRenderWindow>::New();

	renderWindow->SetSize(800, 400);

	renderWindow->AddRenderer(renderer1);

	renderWindow->AddRenderer(renderer2);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =

		vtkSmartPointer<vtkRenderWindowInteractor>::New();

	renderWindowInteractor->SetRenderWindow(renderWindow);



	double leftViewport[] = { 0.0, 0.0, 0.5, 1.0 };

	double rightViewport[] = { 0.5, 0.0, 1.0, 1.0 };



	renderer1->AddActor(oriAxesActor);

	renderer1->AddActor(sphereActor);

	renderer1->AddActor(oriConeActor);

	renderer2->AddActor(axesActor);

	renderer2->AddActor(sphereActor);

	renderer2->AddActor(coneActor);

	renderer2->AddActor2D(textActor);

	renderer1->SetBackground(.3, .3, .5);

	renderer2->SetBackground(.2, .4, .5);

	renderer1->SetViewport(leftViewport);

	renderer2->SetViewport(rightViewport);



	renderWindow->Render();

	renderWindowInteractor->Start();



	return EXIT_SUCCESS;

}
