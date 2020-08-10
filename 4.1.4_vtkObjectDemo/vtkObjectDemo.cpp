#include"vtkSmartPointer.h"
#include"vtkBMPReader.h"
 #include "vtkImageViewer2.h"
 #include"vtkRenderWindowInteractor.h"

 int main(int argc, char*argv[])
 {
	  vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
	   reader->SetFileName("f://White.bmp");
	   reader->Allow8BitBMPOn();
	   // reader->SetDebug(1);
	   reader->SetDebug(0);
    //reader->GlobalWarningDisplayOff();
		 reader->Update();
	
	 vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
	  viewer->SetInputData(reader->GetOutput());
	
	 vtkSmartPointer<vtkRenderWindowInteractor> interactor =
	vtkSmartPointer<vtkRenderWindowInteractor>::New();
	  viewer->SetupInteractor(interactor);
	    viewer->Render();
	
	 interactor->Initialize();
 interactor->Start();

	return 0;
	 }
