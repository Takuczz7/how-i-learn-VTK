
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(Slice)

find_package(VTK 7.0 REQUIRED)
if (NOT VTK_FOUND)
  message("Skipping Slice: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(Slice MACOSX_BUNDLE Slice.cpp )
  target_link_libraries(Slice PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(Slice MACOSX_BUNDLE Slice.cpp )
  target_link_libraries(Slice PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS Slice
    MODULES ${VTK_LIBRARIES}
    )
endif () 
