cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(SBCGuiApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
    # Put this declarations on top!
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SBCGui/qml) # Changed to SBCGui subproject
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick Bluetooth)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

qt_add_executable(SBCGuiApp src/main.cpp # Changed to SBCGui project name
    qmlinterface.h qmlinterface.cpp
    sbcgui.h sbcgui.cpp)

qt_add_qml_module(QmlInterface
    URI QmlInterface
    VERSION 1.0
    SOURCES
        qmlinterface.cpp qmlinterface.h
)

qt_add_resources(SBCGuiApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

# Specify include directories for the core application
target_include_directories(SBCGuiApp PRIVATE
    ${CMAKE_SOURCE_DIR}/SBCCore
    ${CMAKE_SOURCE_DIR}/SBCGui/src
    ${Qt6Bluetooth_INCLUDE_DIRS}
)

target_link_libraries(SBCGuiApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Bluetooth
    SBCCore
)

    # in this files changed all relative paths to the project name
if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS SBCGuiApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
    "Path to the custom QML components defined by the project")
