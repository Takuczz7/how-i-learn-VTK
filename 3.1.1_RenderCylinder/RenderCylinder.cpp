 #include "vtkSmartPointer.h"
 #include "vtkRenderWindow.h"
 #include "vtkRenderer.h"
 #include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
 #include "vtkCylinderSource.h"
 #include "vtkPolyDataMapper.h"
 #include "vtkActor.h"
 #include "vtkProperty.h"
#include "vtkBMPReader.h"
#include "vtkLight.h"
#include "vtkCamera.h"

 int   main()
 {
	 vtkSmartPointer<vtkBMPReader>bmpReader = vtkSmartPointer<vtkBMPReader>::New();
	 bmpReader->SetFileName("f:\\ZK.bmp");
	 vtkSmartPointer<vtkTexture>texture = vtkSmartPointer<vtkTexture>::New();
	 texture->SetInputConnection(bmpReader->GetOutputPort());
	 texture->InterpolateOn();
	 
  vtkSmartPointer<vtkCylinderSource> cylinder =
vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetHeight(6.0);
   cylinder->SetRadius(3.0);
   cylinder->SetResolution(40);

 vtkSmartPointer<vtkPolyDataMapper> cylinderMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
  cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

vtkSmartPointer<vtkActor> cylinderActor =
	 vtkSmartPointer<vtkActor>::New();
  cylinderActor->SetMapper(cylinderMapper);
  cylinderActor->GetProperty()->SetColor(1, 1, 1);
  cylinderActor->RotateX(180);
 vtkSmartPointer<vtkRenderer> renderer =
	vtkSmartPointer<vtkRenderer>::New();
	  renderer->AddActor(cylinderActor);
	  renderer->SetBackground(0.25, 0.5, 1);
	  cylinderActor->SetTexture(texture);

	 vtkSmartPointer<vtkRenderWindow> renWin =
	 vtkSmartPointer<vtkRenderWindow>::New();
	   renWin->AddRenderer(renderer);
	   renWin->SetSize(300, 300);
	
	   
	   vtkSmartPointer<vtkLight> myLightY = vtkSmartPointer<vtkLight>::New();
	   myLightY->SetColor(1, 1, 0);
	   myLightY->SetPosition(0, 1, 1);
	   myLightY->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
	   renderer->AddLight(myLightY);
	   vtkSmartPointer<vtkLight> myLightB = vtkSmartPointer<vtkLight>::New();
	   myLightB->SetColor(0, 0, 1);
	   myLightB->SetPosition(0, -1, -1);
	   myLightB->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
	   renderer->AddLight(myLightB);

	   vtkSmartPointer<vtkCamera>myCamera = vtkSmartPointer<vtkCamera>::New();
	   myCamera->SetFocalPoint(0, 0, 0);
	   myCamera->SetPosition(0, 0, 20);
	   myCamera->ComputeViewPlaneNormal();
	   myCamera->SetViewUp(-0.2234, 0.9983, 0.0345);
	   renderer->SetActiveCamera(myCamera);

	   vtkSmartPointer<vtkRenderWindowInteractor> iren =
		   vtkSmartPointer<vtkRenderWindowInteractor>::New();
	   iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
   iren->SetInteractorStyle(style);

 iren->Initialize();
	   iren->Start();

	return 0;
 }
