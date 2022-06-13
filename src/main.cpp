#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <string>
#include <fstream>


#include "view/Renderer.h"
#include "view/ShaderCompiler.h"
#include "controller/InputHandler.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(){
    // set up the window and OpenGL context. 
    // This will be the object that we call 
    // most of the drawing logic from
    Renderer view;

    if (view.window_fails()){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(view.window);
    glfwSetFramebufferSizeCallback(view.window, framebuffer_size_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // link shaders
    GLuint shaderProgram = ShaderCompiler::createShader("../resources/shaders/vertexShader.glsl", "../resources/shaders/fragmentShader.glsl");
    
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        std::cout << "ISSUE ATTATCHING THE SHADER TO THE PROGRAM\n"  << std::endl;
    }
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // bottom left  0
         0.5f, -0.5f, 0.0f, // bottom right  `1
         0.5f,  0.5f, 0.0f, // top right2
        -0.5f,  0.5f, 0.0f  // top left do this stuff ahaahhahahahahahhahah     3
    }; 

    unsigned indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // holy moly, that's cool
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) 800.0/ (float) 800.0, -0.4f, 5.0f);

    std::cout << glm::to_string(proj) << std::endl;


    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, //layout location  
                          3, // number of values we pass in
                          GL_FLOAT, //value type
                          GL_FALSE, // is this normalized
                          3 * sizeof(float), // how many bytes it is between vertex elements
                          (void*)0); // how many bytes it is until the first element 
    glEnableVertexAttribArray(0);

    GLuint IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);






    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  //  glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // initialize the player and game variables
    InputHandler control(view.window);

    bool game_exit = false;
    const unsigned char* glVer = glGetString(GL_VERSION);
		std::cout << "Currently using " << glVer << std::endl;

    // render loop
    // -----------
    while (view.windowHasNotClosed() && !game_exit){
        // input
        control.processInput();

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(view.window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
