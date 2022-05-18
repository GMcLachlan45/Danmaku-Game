#include <GLFW/glfw3.h>
#include <iostream>

class InputHandler{

    public:
        InputHandler();
        ~InputHandler();

        void initialize_controls();
        void process_input(GLFWwindow *window, float rgb[]);  
};