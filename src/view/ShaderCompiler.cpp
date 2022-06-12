#include "ShaderCompiler.h"

//helper method to read shaders
std::string ShaderCompiler::readFromFile(const std::string filename){
    std::string shaderData;


    std::ifstream fileStream(filename, std::ios::in);
    //tries to open the glsl files
    if(!fileStream.is_open()) { //thow an error if we can't read the file. 
        std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
        return "";
    }

    // read the lines and put it into  a string
    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        shaderData.append(line + "\n");
    }

    fileStream.close();
    return shaderData;
    };

GLuint ShaderCompiler::compileShader(GLuint shaderType, const std::string sourceFile){

    GLuint id = glCreateShader(shaderType);

    // Get the char array for the source data of the glsl
    const std::string src = ShaderCompiler::readFromFile(sourceFile);
    const char * source = src.c_str();
    std::cout<<( (GL_VERTEX_SHADER==shaderType) ? "vert shader \n": "frag shader\n") <<" "<<source<<std::endl;

    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);


    //error Checking for the shader Compilation
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(!result){ // if the compilation fails, say where and why
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length* sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << message<< std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
    };

// take in the shader names to be searched for in shader file
GLuint ShaderCompiler::createShader(const std::string vertexShaderFile, const std::string fragmentShaderFile){
    //create the shader program we're going to use
    GLuint program = glCreateProgram();
    GLuint vertShader = ShaderCompiler::compileShader(GL_VERTEX_SHADER, vertexShaderFile);
    GLuint fragShader = ShaderCompiler::compileShader(GL_FRAGMENT_SHADER, fragmentShaderFile);

    // connect the shader to the program
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
};