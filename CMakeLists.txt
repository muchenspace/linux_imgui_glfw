cmake_minimum_required(VERSION 3.0.0)
project(imgui VERSION 0.1.0)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(
    ./include
    ./include/imgui
    ./include/stb_image
)

file(GLOB_RECURSE src "./src/*.cpp")

add_executable(imgui ${src})
target_link_libraries(imgui  GL glfw)
 
