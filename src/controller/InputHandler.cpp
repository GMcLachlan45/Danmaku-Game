#include "InputHandler.h"

void InputHandler::setup(){
    //TODO Set up the players stuff using the premade Config.json
}

InputHandler::InputHandler(GLFWwindow *window){
    windowptr = window;
}

//Input control, check if the user presses the arrow keys
void InputHandler::processInput() {
    if(glfwGetKey(this->windowptr, GLFW_KEY_UP) == GLFW_PRESS) {
        std::cout<< "Pushed up" <<std::endl;
    }
    if(glfwGetKey(this->windowptr, GLFW_KEY_DOWN) == GLFW_PRESS) {
        std::cout<< "Pushed down" <<std::endl;
    }
    if(glfwGetKey(this->windowptr, GLFW_KEY_LEFT) == GLFW_PRESS) {
        std::cout<< "Pushed left" <<std::endl;
    }
    if(glfwGetKey(this->windowptr, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        std::cout<< "Pushed right" <<std::endl;
    }
    if(glfwGetKey(this->windowptr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        std::cout << "Pushed shift" <<std::endl;
    }
    if (glfwGetKey(this->windowptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->windowptr, true);
}