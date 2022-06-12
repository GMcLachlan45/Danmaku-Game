
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>

class ShaderCompiler{

    public:
        static std::string readFromFile(const std::string);

        static GLuint compileShader(GLuint, const std::string);

        static GLuint createShader(const std::string, const std::string);

};