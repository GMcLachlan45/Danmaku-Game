// System Headers
#include "view/renderer.h"
#include "model/game.h"
#include "controller/process.h"

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <chrono>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);//Callback function prototype declaration


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float rgb[]= {0.0f, 0.0f, 0.0f};

int main() {
    auto time = std::chrono::system_clock::now();
    //Initialize view
    Renderer view;
    Renderer *viewPtr = &view;

    //Initialize model
    Game model;
    Game *modelPtr = &model;

    //Initialize control
    InputHandler control;
    InputHandler *controlPtr = &control;

    //Create a window object
    if (viewPtr->window_fails()) {
        return -1;
    }


    //Notify GLFW to set the context of our window as the main context of the current thread
    glfwMakeContextCurrent(viewPtr->window);
    //Register a callback function for the window. Whenever the window changes size, GLFW will call this function and fill in the corresponding parameters for your processing.
    glfwSetFramebufferSizeCallback(viewPtr->window, framebuffer_size_callback);
    //Initialize the function pointer used by GLAD to manage OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Initializes the player


	const unsigned char* glVer = glGetString(GL_VERSION);
		std::cout << glVer << std::endl;

    bool game_exit = false;
    //Rendering loop
    while(!glfwWindowShouldClose(viewPtr->window)&&!game_exit) {
        // Control
        controlPtr->process_input(viewPtr->window);


        // get how long loop takes
        // Update the Game (model)
        modelPtr->update_game(controlPtr, (float) (std::chrono::system_clock::now()-time).count());
        time = std::chrono::system_clock::now();
        // Display

        // Rendering instructions
        glClearColor(rgb[0], rgb[1], rgb[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Check and call event, exchange buffer
        glfwSwapBuffers(viewPtr->window);//Check the trigger event
        glfwPollEvents();    //Exchange color buffer

    }

    //Release/delete all resources allocated before
    return EXIT_SUCCESS;
}


// When the user changes the size of the window, the viewport should also be adjusted
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // Note: For Retina display, the width and height will be significantly higher than the original input value.

    std::cout << "changed to " << width << " by " << height << std::endl;
    glViewport(0, 0, width, height);
}