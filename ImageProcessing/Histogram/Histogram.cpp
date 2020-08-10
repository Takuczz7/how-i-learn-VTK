#include "vtkSmartPointer.h"
#include "vtkPNGReader.h"
#include"vtkXYPlotActor.h"
#include"vtkImageExtractComponents.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageData.h"
#include "vtkImageAccumulate.h"
#include "vtkImageShiftScale.h"
#include "vtkRenderer.h"
#include "vtkImageActor.h"
int main()
{
	vtkSmartPointer<vtkPNGReader>reader =
vtkSmartPointer<vtkPNGReader>::New();
   reader->SetFileName("F:\\czz\\vtkBuild\\Examples\\ImageProcessing\\Histogram\\Lena.png");
   reader->Update();

int numComponents = reader->GetOutput()->GetNumberOfScalarComponents();

 vtkSmartPointer<vtkXYPlotActor> plot =
vtkSmartPointer<vtkXYPlotActor>::New();
     plot->ExchangeAxesOff();
    plot->SetLabelFormat("%g");
    plot->SetXTitle("Value");
    plot->SetYTitle("Frequency");
    plot->SetXValuesToValue();
	
	double colors[3][3] = {
	        { 1, 0, 0 },
		    { 0, 1, 0 },
		    { 0, 0, 1 }
		 };
	
	 const char* labels[3] = { "Red", "Green", "Blue" };
	
	 int xmax = 0;
	    int ymax = 0;

for (int i = 0; i < numComponents; ++i)
		 {
	        vtkSmartPointer<vtkImageExtractComponents> extract =
			 vtkSmartPointer<vtkImageExtractComponents>::New();
		    extract->SetInputConnection(reader->GetOutputPort());
	        extract->SetComponents(i);
	        extract->Update();
		
		 double range[2];
	        extract->GetOutput()->GetScalarRange(range);
		   int extent = static_cast<int>(range[1]) - static_cast<int>(range[0]) - 1;
		
		 vtkSmartPointer<vtkImageAccumulate> histogram =
			 vtkSmartPointer<vtkImageAccumulate>::New();
	        histogram->SetInputConnection(extract->GetOutputPort());
	        histogram->SetComponentExtent(0, extent, 0, 0, 0, 0);
		    histogram->SetComponentOrigin(range[0], 0, 0);
	        histogram->SetComponentSpacing(1, 0, 0);
		    histogram->SetIgnoreZero(1);
	        histogram->Update();
	
	if (range[1] > xmax)
			 {
			             xmax = range[1];
			       }
		 if (histogram->GetOutput()->GetScalarRange()[1] > ymax)
			 {
			              ymax = histogram->GetOutput()->GetScalarRange()[1];
			        }
		
		       plot->AddDataSetInput(histogram->GetOutput());
		       plot->SetPlotColor(i, colors[i]);
		       plot->SetPlotLabel(i, labels[i]);
		       plot->LegendOn();
	    }

 plot->SetXRange(0, xmax);
    plot->SetYRange(0, ymax);

	vtkSmartPointer<vtkRenderer> renderer =
	 vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(plot);
	
    vtkSmartPointer<vtkRenderWindow> renderWindow =
	 vtkSmartPointer<vtkRenderWindow>::New();
	   renderWindow->AddRenderer(renderer);
	     renderWindow->SetSize(640, 480);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
	 vtkSmartPointer<vtkRenderWindowInteractor>::New();

 interactor->SetRenderWindow(renderWindow);
 interactor->Initialize();
 interactor->Start();

}