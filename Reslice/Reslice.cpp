#include "vtkSmartPointer.h"
#include "vtkMatrix4x4.h"
#include "vtkDICOMImageReader.h"
#include "vtkImageData.h"
#include "vtkImageReslice.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "vtkImageActor.h"
#include "vtkImageMapper3D.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkCommand.h"

class vtkImageInteractionCallback : public vtkCommand
{
public:
	static vtkImageInteractionCallback* New()
	{
		return new vtkImageInteractionCallback;
	}
	vtkImageInteractionCallback()
	{
		this->Slicing = 0;
		this->ImageReslice = nullptr;
		this->Interactor = nullptr;
	}

	void SetImageReslice(vtkImageReslice* reslice)
	{
		this->ImageReslice = reslice;
	}

	void SetMapToColors(vtkImageMapToColors* colors)
	{
		this->MapToColors = colors;
	}

	void SetInteractor(vtkRenderWindowInteractor* interactor)
	{
		this->Interactor = interactor;
	}

	void SetRenderWindow(vtkRenderWindow* window)
	{
		this->RenderWindow = window;
	}

	void Execute(vtkObject* caller, unsigned long eventId, void* callData) override
	{
		int lastPos[2], curPos[2];
		this->Interactor->GetLastEventPosition(lastPos);
		this->Interactor->GetEventPosition(curPos);

		if (eventId == vtkCommand::RightButtonPressEvent)
		{
			this->Slicing = 1;
		}
		else if (eventId == vtkCommand::RightButtonReleaseEvent)
		{
			this->Slicing = 0;
		}
		else if (eventId == vtkCommand::MouseMoveEvent)
		{
			if (this->Slicing)
			{
				int deltaY = lastPos[1] - curPos[1];
				this->ImageReslice->Update();
				double spacing = this->ImageReslice->GetOutput()->GetSpacing()[2];
				vtkMatrix4x4* matrix = this->ImageReslice->GetResliceAxes();
				double point[4], center[4];
				point[0] = 0.0;
				point[1] = 0.0;
				point[2] = spacing * deltaY;
				point[3] = 1.0;

				matrix->MultiplyPoint(point, center);
				matrix->SetElement(0, 3, center[0]);
				matrix->SetElement(1, 3, center[1]);
				matrix->SetElement(2, 3, center[2]);

				this->MapToColors->Update();
				this->OutputImageData = this->MapToColors->GetOutput();

				this->Interactor->Render();
			}
			else
			{
				vtkInteractorStyle* style = vtkInteractorStyle::SafeDownCast(
					this->Interactor->GetInteractorStyle());
				if (style)
				{
					style->OnMouseMove();
				}
			}
		}
	}

private:
	int Slicing;
	vtkImageReslice* ImageReslice;
	vtkImageMapToColors* MapToColors;
	vtkRenderWindowInteractor* Interactor;
	vtkRenderWindow* RenderWindow;
	vtkImageData* OutputImageData;
};

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " DicomDirectory" << std::endl;
		return EXIT_FAILURE;
	}

	auto reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetDirectoryName(argv[1]);
	reader->Update();

	int extent[6];
	double spacing[3];
	double origin[3];
	double center[3];

	reader->GetOutput()->GetExtent(extent);
	reader->GetOutput()->GetSpacing(spacing);
	reader->GetOutput()->GetOrigin(origin);

	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

	static double sagittalElements[16] = {
		0, 0, -1, 0,
		1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, 0, 1 };

	static double cornalElements[16] = {
		1, 0, 0, 0,
		0, 0, 1, 0,
		0, -1, 0, 0,
		0, 0, 0, 1 };

	static double axialElements[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };

	static double obliqueElements[16] = {
		1, 0, 0, 0,
		0, 0.866025, 0.5, 0,
		0,- 0.5, 0.866025, 0,
		0, 0, 0, 1 };

	auto resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
	resliceAxes->DeepCopy(sagittalElements);
	resliceAxes->SetElement(0, 3, center[0]);
	resliceAxes->SetElement(1, 3, center[1]);
	resliceAxes->SetElement(2, 3, center[2]);



	auto ImageReslice = vtkSmartPointer<vtkImageReslice>::New();
	ImageReslice->SetInputConnection(reader->GetOutputPort());
	ImageReslice->SetOutputDimensionality(2);

	ImageReslice->SetResliceAxes(resliceAxes);


	ImageReslice->SetResliceAxesOrigin(center);

	ImageReslice->SetInterpolationModeToLinear();

	auto lookupTable = vtkSmartPointer<vtkLookupTable>::New();
	lookupTable->SetRange(-2000, 2000);
	lookupTable->SetValueRange(0.0, 1.0);
	lookupTable->SetSaturationRange(0.0, 0.0);
	lookupTable->SetRampToLinear();
	lookupTable->Build();

	auto mapToColors = vtkSmartPointer<vtkImageMapToColors>::New();
	mapToColors->SetLookupTable(lookupTable);
	mapToColors->SetInputConnection(ImageReslice->GetOutputPort());
	mapToColors->Update();

	auto imageActor = vtkSmartPointer<vtkImageActor>::New();
	imageActor->GetMapper()->SetInputConnection(mapToColors->GetOutputPort());

	auto renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(imageActor);

	auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	auto imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();

	auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetInteractorStyle(imageStyle);
	interactor->SetRenderWindow(renderWindow);
	interactor->Initialize();

	auto callback = vtkSmartPointer<vtkImageInteractionCallback>::New();
	callback->SetImageReslice(ImageReslice);
	callback->SetMapToColors(mapToColors);
	callback->SetInteractor(interactor);
	callback->SetRenderWindow(renderWindow);

	imageStyle->AddObserver(vtkCommand::RightButtonPressEvent, callback);
	imageStyle->AddObserver(vtkCommand::RightButtonReleaseEvent, callback);
	imageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);

	interactor->Start();

	return EXIT_SUCCESS;
}
