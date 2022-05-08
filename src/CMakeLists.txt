cmake_minimum_required(VERSION 3.12)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
project(Danmaku-Game)
find_package(glfw3 REQUIRED)
file(GLOB project_file glad.c main.cpp)
add_executable(danmaku ${project_file})

target_link_libraries(danmaku
    -lglfw3
    -lGL
    -lm
    -lXrandr
    -lXi
    -lX11
#    -lXxf86vm
    -lpthread
    -ldl
    -lXinerama
    -lXcursor
    )