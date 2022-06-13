#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <iostream>

class Renderer {

    // default screen size settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 800;


    void setup();

    public:
        GLFWwindow *window;

        Renderer();
        ~Renderer();

        void initialize();
        bool window_fails();

        bool windowHasNotClosed();



        void render();
};
