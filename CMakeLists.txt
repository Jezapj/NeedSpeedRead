cmake_minimum_required(VERSION 3.20)
project(NeedSpeedRead LANGUAGES CXX)
find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(core)
add_subdirectory(backend)
add_subdirectory(gui)

# Make your main application depend on this copy step
add_dependencies(${PROJECT_NAME} copy_xpdf_tools)