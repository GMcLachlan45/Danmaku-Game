// System Headers
#include "view/Renderer.h"
#include "model/Game.h"
#include "controller/InputHandler.h"

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
        std::cout<< "Window failed" << std::endl;
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
	
	
	// initialize shaders
	
    GLuint shader = Renderer::createShader(
        "../resources/shaders/vertexShader.glsl", 
        "../resources/shaders/fragmentShader.glsl");

    glUseProgram(shader);
	
	
	
						
						
					//		x		y	  z		rgb
    float vertices[24] = {-0.5f,  0.5f, 0.0f,// 0.0f, 0.0f, 0.0f,
                          -0.5f, -0.5f, 0.0f,// 0.0f, 0.0f, 0.0f,
                           0.5f, -0.5f, 0.0f,// 0.0f, 0.0f, 0.0f,
						   0.5f,  0.5f, 0.0f};//, 0.0f, 0.0f, 0.0f};

    //Vertex Buffer
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Sends Vertices to the GPU
	
	
	
//						tl bl br tr
    GLuint indices[6] = {0,1,2,3};
	
	// Index Buffer
    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	
	
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

	// Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    glEnableVertexAttribArray(0);
	

	// Color
   // glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));





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
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//rgb[0], rgb[1], rgb[2], 1.0f);
		
		
        glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(viewPtr->window);
        
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







    