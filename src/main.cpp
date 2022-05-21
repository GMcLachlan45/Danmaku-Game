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

    //Initialize the function pointer used by GLAD to manage OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //Initializes the player
	const unsigned char* glVer = glGetString(GL_VERSION);
		std::cout << glVer << std::endl;

    //Create a window object
    if (viewPtr->window_fails()) {
        std::cout<< "window failed" << std::endl;
        return -1;
    }

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
        
        viewPtr->render();
        
        //Check the trigger event
        glfwPollEvents();    

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







    // std::cout << "Got 1" << std::endl;

    // float positions[6] = {-0.5f, -0.5f,
    //                      -0.5f, 0.5f,
    //                       0.0f, 0.5f};
    
    // std::cout << "Got 2" << std::endl;

    // GLuint buffer;

    // std::cout << "Got 3" << std::endl;
    // glGenBuffers(1, &buffer); 

    // std::cout << "Got 4" << std::endl;
    // glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // std::cout << "Got 5" << std::endl;
    // glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // std::cout << "Got 6" << std::endl;

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);


    // GLuint shader = Renderer::createShader("vertexShader", "fragmentShader");
