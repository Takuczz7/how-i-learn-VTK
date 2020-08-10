#include"vtkSmartPointer.h"
  #include"vtkConeSource.h"
 #include"vtkPolyDataMapper.h"
 #include"vtkRenderWindow.h"
 #include"vtkRenderWindowInteractor.h"
 #include"vtkCamera.h"
 #include"vtkActor.h"
 #include"vtkRenderer.h"
 #include"vtkCommand.h"
#include"vtkBoxWidget.h"
#include"vtkTransform.h"
 #include"vtkInteractorStyleTrackballCamera.h"
#include "vtkCallbackCommand.h"


 //第一步
class vtkMyCallback:public vtkCommand
 {
	  public:
		 static vtkMyCallback *New()
			 { return new vtkMyCallback; }
		
			 virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData)
			{
		        vtkTransform *t = vtkTransform::New();
			        vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
		       widget->GetTransform(t);
			     widget->GetProp3D()->SetUserTransform(t);
			        t->Delete();
			     }
		 };

int main()
{
	   vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
	   cone->SetHeight(3.0);
	    cone->SetRadius(1.0);
	   cone->SetResolution(10);
	
	 vtkSmartPointer<vtkPolyDataMapper> coneMapper =
		 vtkSmartPointer<vtkPolyDataMapper>::New();
	  coneMapper->SetInputConnection(cone->GetOutputPort());
	
 vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
	   coneActor->SetMapper(coneMapper);
	
	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
	  ren1->AddActor(coneActor);
	   ren1->SetBackground(0.1, 0.2, 0.4);
	
	 vtkSmartPointer<vtkRenderWindow> renWin =
		 vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	   renWin->SetSize(300, 300);
	
	 vtkSmartPointer<vtkRenderWindowInteractor> iren =
		 vtkSmartPointer<vtkRenderWindowInteractor>::New();
	   iren->SetRenderWindow(renWin);
	
	 vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
		 vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	   iren->SetInteractorStyle(style);
	
 //通过vtkBoxWidget可以控制coneActor的变换矩阵，从而实现coneActor的形变
	 vtkSmartPointer<vtkBoxWidget> boxWidget = vtkSmartPointer<vtkBoxWidget>::New();
  boxWidget->SetInteractor(iren);
   boxWidget->SetPlaceFactor(1.25);
	   boxWidget->SetProp3D(coneActor);
	  boxWidget->PlaceWidget();
	
	   
		 vtkSmartPointer<vtkMyCallback> callback = vtkSmartPointer<vtkMyCallback>::New();
	
  
	 boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
	
	   //激活Widget。按“i”键可以关闭或激活Widget。
		 boxWidget->On();
	
	 iren->Initialize();
	   iren->Start();
	
	 return 0;
	 }
