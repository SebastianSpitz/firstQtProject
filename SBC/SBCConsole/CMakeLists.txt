cmake_minimum_required(VERSION 3.14)

project(SBCConsole LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Bluetooth Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Bluetooth Core)

add_executable(SBCConsole
  main.cpp
)
target_link_libraries(SBCConsole
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Bluetooth
    SBCCore
)

# Specify include directories for the core application
target_include_directories(SBCConsole PRIVATE ${CMAKE_SOURCE_DIR}/SBCCore)

include(GNUInstallDirs)
install(TARGETS SBCConsole
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
