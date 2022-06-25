#include "InputHandler.h"

void InputHandler::setup(){
    //TODO Set up the players stuff using the premade Config.json
}

InputHandler::InputHandler(GLFWwindow *window){
    windowPtr = window;
}

//Input control, check if the user presses the arrow keys
void InputHandler::processInput() {
    buttonInputs[0] =(glfwGetKey(this->windowPtr, GLFW_KEY_UP) == GLFW_PRESS);
    buttonInputs[1] =(glfwGetKey(this->windowPtr, GLFW_KEY_DOWN) == GLFW_PRESS);
    buttonInputs[2] =(glfwGetKey(this->windowPtr, GLFW_KEY_LEFT) == GLFW_PRESS);
    buttonInputs[3] =(glfwGetKey(this->windowPtr, GLFW_KEY_RIGHT) == GLFW_PRESS);
    buttonInputs[4] =(glfwGetKey(this->windowPtr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
    // std::cout << buttonInputs[0]<< " "
    // << buttonInputs[1]<< " "
    // << buttonInputs[2]<< " "
    // << buttonInputs[3]<< " "
    // << buttonInputs[4]<< " " <<std::endl;
    if (glfwGetKey(this->windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->windowPtr, true);
}

bool* InputHandler::getInput() {return this->buttonInputs;}