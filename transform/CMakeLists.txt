
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(transform)

find_package(VTK 7.0 REQUIRED)
if (NOT VTK_FOUND)
  message("Skipping Slice: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(transform MACOSX_BUNDLE transform.cpp )
  target_link_libraries(transform PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(transform MACOSX_BUNDLE transform.cpp )
  target_link_libraries(transform PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS transform
    MODULES ${VTK_LIBRARIES}
    )
endif () 
