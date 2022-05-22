#include "Renderer.h"

Renderer::Renderer(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 400, "Danmaku", NULL, NULL);

};

Renderer::~Renderer(){
    glfwTerminate();
};

void Renderer::initialize(){};

bool Renderer::window_fails(){
    return window == NULL;
};

void Renderer::render(){
    glClear(GL_COLOR_BUFFER_BIT);

    //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);//rgb[0], rgb[1], rgb[2], 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
};


//helper method to read shaders
std::string Renderer::readFromFile(const std::string filename){
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
    
GLuint Renderer::compileShader(GLuint shaderType, const std::string sourceFile){
    GLuint id = glCreateShader(shaderType);

    // Get the char array for the source data of the glsl
    const std::string src = readFromFile(sourceFile);
    const char * source = src.c_str();

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
    }

    return id;
    };

// take in the shader names to be searched for in shader file
GLuint Renderer::createShader(const std::string vertexShaderFile, const std::string fragmentShaderFile){
    //create the shader program we're going to use
    GLuint program = glCreateProgram();
    GLuint vertShader = Renderer::compileShader(GL_VERTEX_SHADER, vertexShaderFile);
    GLuint fragShader = Renderer::compileShader(GL_FRAGMENT_SHADER, fragmentShaderFile);

    // connect the shader to the program
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
};
