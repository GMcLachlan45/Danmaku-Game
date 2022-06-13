#include "Renderer.h"

void Renderer::setup(){
    // look at the config file to see the desired dimensions and monitor and settings and stuff
}

Renderer::Renderer(){


    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(this->SCR_WIDTH, this->SCR_HEIGHT, "Danmaku Game", NULL, NULL);
};

Renderer::~Renderer(){
    glfwTerminate();
};

void Renderer::initialize(){};

bool Renderer::window_fails(){
    return window == NULL;
};
bool Renderer::windowHasNotClosed(){return !glfwWindowShouldClose(window);}

void Renderer::render(){
    glClear(GL_COLOR_BUFFER_BIT);

   // glClearColor(1.0f, 0.0f, 0.0f, 1.0f);//rgb[0], rgb[1], rgb[2], 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
};
