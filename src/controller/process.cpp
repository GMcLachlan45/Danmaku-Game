#include "process.h"

InputHandler::InputHandler(){};
InputHandler::~InputHandler(){};

void InputHandler::initialize_controls(){
    // Todo when game is looking epic
    // essentially, read a config file,
    // and let the player choose their
    // keybinds and stuff
};

void InputHandler::process_input(GLFWwindow *window, float rgb[]){
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        std::cout<< "Pushed up" <<std::endl;
        rgb[0]+=0.004;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        std::cout<< "Pushed down" <<std::endl;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        std::cout<< "Pushed left" <<std::endl;
        rgb[1]+=0.004;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        std::cout<< "Pushed right" <<std::endl;   
        rgb[2]+=0.004;     
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        std::cout << "Pushed shift" <<std::endl;
        rgb[0]=rgb[1]=rgb[2]=0.0f;
    }
};