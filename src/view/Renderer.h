#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <iostream>

class Renderer {
    public:
        GLFWwindow *window;

        Renderer();
        ~Renderer();

        void initialize();
        bool window_fails();
        void render();

        static std::string readFromFile(std::string filename);

        static GLuint compileShader(unsigned int shaderType, std::string sourceFile);

        static GLuint createShader(
            std::string vertexShaderFile,
            std::string fragmentShaderFile);
};
