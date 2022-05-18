#include "renderer.h"

Renderer::Renderer(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 400, "Danmaku", NULL, NULL);
};

Renderer::~Renderer(){
    glfwTerminate();
};

void Renderer::initialize(){};

bool Renderer::window_fails(){
    return window == NULL;
};

void Renderer::render(){};

