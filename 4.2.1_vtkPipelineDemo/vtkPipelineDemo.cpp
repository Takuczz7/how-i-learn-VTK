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
   //读入Structured_Points类型的vtk文件。
     vtkSmartPointer<vtkStructuredPointsReader> reader =
	 vtkSmartPointer<vtkStructuredPointsReader>::New();
     reader->SetFileName("F://czz//Data//carotid.vtk");

   //用移动立方体法提取等值面。
	 vtkSmartPointer<vtkMarchingCubes> marchingCubes =
     vtkSmartPointer<vtkMarchingCubes>::New();

	 auto data = reader->GetOutput();
	 std::cout << *data << std::endl;

     marchingCubes->SetInputConnection(reader->GetOutputPort());
     marchingCubes->SetValue(0, 500);
	
	  //将生成的等值面数据进行Mapper
	 vtkSmartPointer<vtkPolyDataMapper> mapper =
	 vtkSmartPointer<vtkPolyDataMapper>::New();
	 mapper->SetInputConnection(marchingCubes->GetOutputPort());
	
	   //把Mapper的输出送入渲染引擎进行显示
		 //////////////////////////////////////渲染引擎部分////////////////////////////////////
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
