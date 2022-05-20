#include "process.h"

InputHandler::InputHandler(){};
InputHandler::~InputHandler(){};

void InputHandler::initialize_controls(){
    up = down = left = right = shift = false;
    // Todo when game is looking epic
    // essentially, read a config file,
    // and let the player choose their
    // keybinds and stuff
};

void InputHandler::process_input(GLFWwindow *window){
    up = (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS);
    down = (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS);
    left = (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
    right = (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
    shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
};