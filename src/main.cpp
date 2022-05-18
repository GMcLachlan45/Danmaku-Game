// System Headers
#include "view/renderer.h"
#include "model/game.h"
#include "controller/process.h"

// Standard Headers
#include <cstdio>
#include <cstdlib>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);//Callback function prototype declaration


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float rgb[]= {0.0f, 0.0f, 0.0f};

int main() {
    //Initialize view
    Renderer rend;

    //Initialize model 
    Game ng;

    //Initialize control
    InputHandler control;

    //Create a window object
    if (rend.window_fails()) {
        return -1;
    }


    //Notify GLFW to set the context of our window as the main context of the current thread
    glfwMakeContextCurrent(rend.window);
    //Register a callback function for the window. Whenever the window changes size, GLFW will call this function and fill in the corresponding parameters for your processing.
    glfwSetFramebufferSizeCallback(rend.window, framebuffer_size_callback);
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
    while(!glfwWindowShouldClose(rend.window)&&!game_exit) {
        // Control
        control.process_input(rend.window, rgb);

        // Update the Game (model)

        // Display

        // Rendering instructions
        glClearColor(rgb[0], rgb[1], rgb[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Check and call event, exchange buffer
        glfwSwapBuffers(rend.window);//Check the trigger event
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