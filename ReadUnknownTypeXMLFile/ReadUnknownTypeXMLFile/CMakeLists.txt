
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(ReadUnknownTypeXMLFile)

find_package(VTK COMPONENTS 
  vtkCommonColor
  vtkCommonCore
  vtkCommonDataModel
  vtkIOXML
  vtkInteractionStyle
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2 QUIET)
if (NOT VTK_FOUND)
  message("Skipping ReadUnknownTypeXMLFile: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(ReadUnknownTypeXMLFile MACOSX_BUNDLE ReadUnknownTypeXMLFile.cxx )
  target_link_libraries(ReadUnknownTypeXMLFile PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(ReadUnknownTypeXMLFile MACOSX_BUNDLE ReadUnknownTypeXMLFile.cxx )
  target_link_libraries(ReadUnknownTypeXMLFile PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS ReadUnknownTypeXMLFile
    MODULES ${VTK_LIBRARIES}
    )
endif () 
