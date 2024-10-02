cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(ClientGuiApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ClientGui/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick Bluetooth)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

set(CMAKE_AUTORCC ON)
qt_add_executable(ClientGuiApp src/main.cpp
    qmlinterface.h qmlinterface.cpp
    clientgui.h clientgui.cpp
    resources.qrc
)

qt_add_qml_module(QmlInterface
    URI QmlInterface
    VERSION 1.0
    SOURCES
        qmlinterface.cpp qmlinterface.h
)

qt_add_resources(ClientGuiApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

# Defining the qml designs.qml singleton
set_source_files_properties(content/Designs.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(Designs
    URI Designs
    QML_FILES content/Designs.qml
)

target_link_libraries(ClientGuiApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Bluetooth
    ClientCore
)

# Specify include directories for the console application
target_include_directories(ClientGuiApp PRIVATE ${CMAKE_SOURCE_DIR}/ClientCore)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS ClientGuiApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
    "Path to the custom QML components defined by the project")



