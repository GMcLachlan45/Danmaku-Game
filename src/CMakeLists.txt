cmake_minimum_required(VERSION 3.21)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
project(Danmaku-Game)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
file(GLOB project_file main.cpp model/glad.c 
	 model/game.cpp controller/process.cpp 
	 view/renderer.cpp)
add_executable(danmaku ${project_file})

if (UNIX)
        message(STATUS "Based Linux Chad")
	target_link_libraries(danmaku
		-lglfw3
		-lGL
		-lm
		-lXrandr
		-lXi
		-lX11
		-lXxf86vm
		-lpthread
		-ldl
		-lXinerama
		-lXcursor
	)
elseif(WIN32)
        message(STATUS "Based Windows Enjoyer")
	target_link_libraries(danmaku
		-lglfw3
		-lopengl32
		-lm
		-lpthread
		-ldl
	)
else()
        message(STATUS ">being an Apple cuck")
endif()
	

