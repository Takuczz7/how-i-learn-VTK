cmake_minimum_required( VERSION 3.3 FATAL_ERROR )
project( MPR )
 
#----------------------------------------------------------------------------------
find_package( VTK REQUIRED )
find_package( Qt5Widgets REQUIRED )
 
include( ${VTK_USE_FILE} )

 
#----------------------------------------------------------------------------------
SET( PROJECT_SRCS
    main.cpp
    MainWindow.cpp
    )
 
SET( PROJECT_UIS
    MainWindow.ui
)
 
SET( PROJECT_MOC_HDRS
  MainWindow.h
)
 
#----------------------------------------------------------------------------------
QT5_WRAP_UI( PROJECT_UIS_H
             ${PROJECT_UIS}
           )
 
QT5_WRAP_CPP( PROJECT_MOC_SRCS
              ${PROJECT_MOC_HDRS}
            )
 
#----------------------------------------------------------------------------------
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${VTK_DIR}
                   )
 
ADD_EXECUTABLE( MPR
                ${PROJECT_SRCS}
                ${PROJECT_UIS_H}
                ${PROJECT_MOC_SRCS}
              )
 
TARGET_LINK_LIBRARIES (MPR
  ${VTK_LIBRARIES}
  ${Qt5Widgets_LIBRARIES}
  )
