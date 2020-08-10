#-------------------------------------------------
#
# Project created by QtCreator 2018-04-20T10:33:51
#
#-------------------------------------------------

QT       += core gui
CONFIG  += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FourPanelViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += F:\VTK-7.1\releaselib5.3\include\vtk-7.1

LIBS += -LF:\\VTK-7.1\\releaselib5.3\\lib \
        libvtkCommonCore-7.1 \
        libvtkIOImage-7.1 \
        libvtkRenderingCore-7.1 \
        libvtkRenderingOpenGL2-7.1 \
        libvtkRenderingFreeType-7.1 \
        libvtkFiltersSources-7.1 \
        libvtkFiltersCore-7.1 \
        libvtkFiltersModeling-7.1 \
        libvtkFiltersExtraction-7.1 \
        libvtkFiltersGeometry-7.1 \
        libvtkFiltersHybrid-7.1 \
        libvtkDICOMParser-7.1 \
        libvtkImagingCore-7.1 \
        libvtkImagingColor-7.1 \
        libvtkImagingHybrid-7.1 \
        libvtkImagingGeneral-7.1 \
        libvtkImagingFourier-7.1 \
        libvtkImagingMath-7.1 \
        libvtkImagingMorphological-7.1 \
        libvtkRenderingVolume-7.1 \
        libvtkRenderingVolumeOpenGL2-7.1 \
        libvtkRenderingContext2D-7.1 \
        libvtkRenderingContextOpenGL2-7.1 \
        libvtkRenderingQt-7.1 \
        libvtkRenderingAnnotation-7.1 \
        libvtkRenderingLOD-7.1 \
        libvtkFiltersGeneral-7.1 \
        libvtkChartsCore-7.1 \
        libvtkCommonComputationalGeometry-7.1 \
        libvtkCommonMath-7.1 \
        libvtkCommonTransforms-7.1 \
        libvtkCommonMisc-7.1 \
        libvtkCommonSystem-7.1 \
        libvtkCommonDataModel-7.1 \
        libvtkCommonExecutionModel-7.1 \
        libvtkCommonColor-7.1 \
        libvtkCommonTransforms-7.1 \
        libvtkInteractionImage-7.1 \
        libvtkInteractionStyle-7.1 \
        libvtkInteractionWidgets-7.1 \
        libvtkImagingSources-7.1 \
        libvtkIOXML-7.1 \
        libvtkIOLegacy-7.1 \
        libvtkIOGeometry-7.1 \
        libvtkGUISupportQt-7.1 \
        libvtkGeovisCore-7.1 \
        libvtkViewsContext2D-7.1 \
        libvtksys-7.1 \
