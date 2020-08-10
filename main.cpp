#include "mainwindow.h"
#include <QApplication>

#ifndef INITIAL_OPENGL
#define INITIAL_OPENGL
#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)
VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkRenderingContextOpenGL2)
#endif

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkMarchingCubes.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkStripper.h>
#include <vtkDICOMImageReader.h>
#include <array>
#include<vtkInteractorStyleTrackballCamera.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    vtkSmartPointer< vtkDICOMImageReader > reader =
      vtkSmartPointer< vtkDICOMImageReader >::New();
    reader->SetDirectoryName("../DICOM/133ceng");
    reader->Update();
    int imageDims[3];//256-256-20
    reader->GetOutput()->GetDimensions(imageDims);

    vtkSmartPointer<vtkNamedColors> colors =
      vtkSmartPointer<vtkNamedColors>::New();

    std::array<unsigned char , 4> skinColor{{255, 125, 64}};
      colors->SetColor("SkinColor", skinColor.data());
    std::array<unsigned char , 4> bkg{{51, 77, 102, 255}};
      colors->SetColor("BkgColor", bkg.data());

    vtkSmartPointer<vtkRenderer> aRenderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(aRenderer);
    vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);

    vtkInteractorStyleTrackballCamera* style = vtkInteractorStyleTrackballCamera::New();
    iren->SetInteractorStyle(style);

    aRenderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
    renWin->SetSize(640, 480);

    vtkSmartPointer<vtkLookupTable> bwLut =
      vtkSmartPointer<vtkLookupTable>::New();
    bwLut->SetTableRange (0, 1000);
    bwLut->SetSaturationRange (0, 0);
    bwLut->SetHueRange (0, 0);
    bwLut->SetValueRange (0, 1);
    bwLut->Build(); //effective built

    vtkSmartPointer<vtkLookupTable> hueLut =
      vtkSmartPointer<vtkLookupTable>::New();
    hueLut->SetTableRange (0, 1000);
    hueLut->SetHueRange (0, 1);
    hueLut->SetSaturationRange (1, 1);
    hueLut->SetValueRange (1, 1);
    hueLut->Build(); //effective built

    vtkSmartPointer<vtkLookupTable> satLut =
      vtkSmartPointer<vtkLookupTable>::New();
    satLut->SetTableRange (0, 1000);
    satLut->SetHueRange (.6, .6);
    satLut->SetSaturationRange (0, 1);
    satLut->SetValueRange (1, 1);
    satLut->Build(); //effective built

    vtkSmartPointer<vtkImageMapToColors> sagittalColors =
      vtkSmartPointer<vtkImageMapToColors>::New();
    sagittalColors->SetInputConnection(reader->GetOutputPort());
    sagittalColors->SetLookupTable(bwLut);
    sagittalColors->Update();

    vtkSmartPointer<vtkImageActor> sagittal =
      vtkSmartPointer<vtkImageActor>::New();
    sagittal->GetMapper()->SetInputConnection(sagittalColors->GetOutputPort());
    sagittal->SetDisplayExtent(imageDims[0]/2, imageDims[0]/2, 0,imageDims[1], 0,imageDims[2]);

    vtkSmartPointer<vtkImageMapToColors> axialColors =
      vtkSmartPointer<vtkImageMapToColors>::New();
    axialColors->SetInputConnection(reader->GetOutputPort());
    axialColors->SetLookupTable(hueLut);
    axialColors->Update();

    vtkSmartPointer<vtkImageActor> axial =
      vtkSmartPointer<vtkImageActor>::New();
    axial->GetMapper()->SetInputConnection(axialColors->GetOutputPort());
    axial->SetDisplayExtent(0,imageDims[0], 0,imageDims[1], imageDims[2]/2,imageDims[2]/2);

    vtkSmartPointer<vtkImageMapToColors> coronalColors =
      vtkSmartPointer<vtkImageMapToColors>::New();
    coronalColors->SetInputConnection(reader->GetOutputPort());
    coronalColors->SetLookupTable(satLut);
    coronalColors->Update();

    vtkSmartPointer<vtkImageActor> coronal =
      vtkSmartPointer<vtkImageActor>::New();
    coronal->GetMapper()->SetInputConnection(coronalColors->GetOutputPort());
    coronal->SetDisplayExtent(0,imageDims[0], imageDims[1]/2,imageDims[1]/2, 0,imageDims[2]);

    vtkSmartPointer<vtkCamera> aCamera =
      vtkSmartPointer<vtkCamera>::New();
    aCamera->SetViewUp (0, 0, -1);
    aCamera->SetPosition (0, -1, 0);
    aCamera->SetFocalPoint (0, 0, 0);
    aCamera->ComputeViewPlaneNormal();
    aCamera->Azimuth(30.0);
    aCamera->Elevation(30.0);

    aRenderer->AddActor(sagittal);
    aRenderer->AddActor(axial);
    aRenderer->AddActor(coronal);

    aRenderer->SetActiveCamera(aCamera);

    renWin->Render();

    aRenderer->ResetCamera ();
    aCamera->Dolly(1.5);

    aRenderer->ResetCameraClippingRange ();

    // interact with data
    iren->Initialize();
    iren->Start();

    return a.exec();
}
