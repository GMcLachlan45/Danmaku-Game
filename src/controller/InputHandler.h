#ifndef GAME_INPUT
#define GAME_INPUT

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


class InputHandler{

    GLFWwindow* windowPtr;
    bool *buttonInputs = new bool[5]{false,false,false,false,false};

        void setup();
    public:
        InputHandler(GLFWwindow *window);
        void processInput();

        bool *getInput();
};  

#endif