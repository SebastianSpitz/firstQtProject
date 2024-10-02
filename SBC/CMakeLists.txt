cmake_minimum_required(VERSION 3.14)

# Define the project
project(SBC VERSION 0.1 LANGUAGES CXX)

# Add subdirectories for SBC components
add_subdirectory(SBCCore)
add_subdirectory(SBCConsole)
add_subdirectory(SBCGui)
