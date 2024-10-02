cmake_minimum_required(VERSION 3.14)

# Define the project
project(Client VERSION 0.1 LANGUAGES CXX)

# Add subdirectories for SBC components
add_subdirectory(ClientCore)
add_subdirectory(ClientConsole)
add_subdirectory(ClientGui)

