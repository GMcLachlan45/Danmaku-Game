
#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <GLFW/glfw3.h>
#include <iostream>

class InputHandler{
    public:
    bool up, down, left, right, shift;
    
        InputHandler();
        ~InputHandler();

        void initialize_controls();
        void process_input(GLFWwindow *window);  
};

#endif