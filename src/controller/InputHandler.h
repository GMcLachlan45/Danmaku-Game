
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class InputHandler{

    GLFWwindow* windowptr;

        void setup();
    public:
        InputHandler(GLFWwindow *window);
        void processInput();
};