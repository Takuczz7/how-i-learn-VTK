#include "vtkSmartPointer.h"
#include "vtkStructuredPoints.h"
 #include "vtkStructuredPointsReader.h"
 #include "vtkRenderer.h"
 #include "vtkRenderWindow.h"
 #include "vtkRenderWindowInteractor.h"
 #include "vtkMarchingCubes.h"
 #include "vtkPolyDataMapper.h"
 #include "vtkActor.h"
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)

int main(int argc, char *argv[])
{
   //����Structured_Points���͵�vtk�ļ���
     vtkSmartPointer<vtkStructuredPointsReader> reader =
	 vtkSmartPointer<vtkStructuredPointsReader>::New();
     reader->SetFileName("F://czz//Data//carotid.vtk");

   //���ƶ������巨��ȡ��ֵ�档
	 vtkSmartPointer<vtkMarchingCubes> marchingCubes =
     vtkSmartPointer<vtkMarchingCubes>::New();

	 auto data = reader->GetOutput();
	 std::cout << *data << std::endl;

     marchingCubes->SetInputConnection(reader->GetOutputPort());
     marchingCubes->SetValue(0, 500);
	
	  //�����ɵĵ�ֵ�����ݽ���Mapper
	 vtkSmartPointer<vtkPolyDataMapper> mapper =
	 vtkSmartPointer<vtkPolyDataMapper>::New();
	 mapper->SetInputConnection(marchingCubes->GetOutputPort());
	
	   //��Mapper�����������Ⱦ���������ʾ
		 //////////////////////////////////////��Ⱦ���沿��////////////////////////////////////
	 vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	 actor->SetMapper(mapper);
	
	 vtkSmartPointer<vtkRenderWindow> renWin =
	 vtkSmartPointer<vtkRenderWindow>::New();
     vtkSmartPointer<vtkRenderer> renderer =
	 vtkSmartPointer<vtkRenderer>::New();
	 vtkSmartPointer<vtkRenderWindowInteractor> interactor =
	 vtkSmartPointer<vtkRenderWindowInteractor>::New();
	
	 renderer->AddActor(actor);
	  renWin->AddRenderer(renderer);
	  interactor->SetRenderWindow(renWin);
     
      renderer->Render();
	
      interactor->Initialize();
	  interactor->Start();
	  //////////////////////////////////////////////////////////////////////////////////////////////////
	
		 return 0;
	 }
