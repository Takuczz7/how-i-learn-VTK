cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

PROJECT(PickPixel)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(PickPixel MACOSX_BUNDLE PickPixel.cpp)

if(VTK_LIBRARIES)
  target_link_libraries(PickPixel ${VTK_LIBRARIES})
else()
  target_link_libraries(PickPixel vtkHybrid vtkWidgets)
endif()