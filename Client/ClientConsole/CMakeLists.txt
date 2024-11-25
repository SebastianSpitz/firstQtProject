cmake_minimum_required(VERSION 3.14)

project(ClientConsole LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(ClientConsole
  main.cpp
)

target_link_libraries(ClientConsole
    Qt${QT_VERSION_MAJOR}::Core
    ClientCore
)

# Specify include directories for the console application
target_include_directories(ClientConsole PRIVATE ${CMAKE_SOURCE_DIR}/ClientCore)

include(GNUInstallDirs)
install(TARGETS ClientConsole
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
