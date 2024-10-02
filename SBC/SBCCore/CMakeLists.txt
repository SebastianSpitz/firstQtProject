cmake_minimum_required(VERSION 3.14)

project(SBCCore LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Bluetooth)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Bluetooth)

add_library(SBCCore STATIC
  sbccore.cpp
  sbccore.h
  bleserver.h bleserver.cpp
  sbcio.h sbcio.cpp
)

# Specify include directories for the library
target_include_directories(SBCCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt6Bluetooth_INCLUDE_DIRS}
)

target_link_libraries(SBCCore PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Bluetooth
)
