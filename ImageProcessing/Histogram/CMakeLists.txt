
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(Histogram)

find_package(VTK 7.0 REQUIRED)
if (NOT VTK_FOUND)
  message("Skipping Histogram: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(Histogram MACOSX_BUNDLE Histogram.cpp )
  target_link_libraries(Histogram PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(Histogram MACOSX_BUNDLE Histogram.cpp )
  target_link_libraries(Histogram PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS Histogram
    MODULES ${VTK_LIBRARIES}
    )
endif () 
