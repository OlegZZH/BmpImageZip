
cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" OFF)
option(BUILD_QDS_COMPONENTS "Build design studio components" OFF)

project(TestApp LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Widgets Qml Quick  )
qt_standard_project_setup()

add_subdirectory(CompressorLib CompressorLib_build)

qt_add_executable(${CMAKE_PROJECT_NAME}
        App/Model/model.cpp
        App/Model/model.h
        App/Model/filesListModel.cpp
        App/Model/filesListModel.h
        App/Model/file.cpp
        App/Model/file.h
        App/Controller/controller.cpp
        App/Controller/controller.h
        App/Controller/taskResult.h
        App/Controller/taskResult.cpp
        App/Controller/asyncDecorator.h
        App/logger.h
        App/macros.h
        CompressorLib/compressor.h)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE compressor)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ../CompressorLib)

qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf)

include(qds)

if (BUILD_QDS_COMPONENTS)
    include(qmlcomponents OPTIONAL)
endif()

if (LINK_INSIGHT)
    include(insight OPTIONAL)
endif ()

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
