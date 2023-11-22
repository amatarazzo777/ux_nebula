cmake_minimum_required(VERSION 3.13)  # CMake version check
project(test0)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 17)            # Enable c++14 standard

# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES main.cpp vm/base/vector_font.cpp vm/base/view_manager.cpp vm/os/linux_xcb/os_interface.cpp)
file(GLOB SOURCES "vm/base/*.cpp")
file(GLOB SOURCES "vm/os/linux_xcb/*.cpp")

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(test0 ${SOURCE_FILES})
