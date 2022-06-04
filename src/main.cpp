// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <iostream>


//helper method to read shaders
std::string readFromFile(const std::string filename){
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

GLuint compileShader(GLuint shaderType, const std::string sourceFile){
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
GLuint createShader(const std::string vertexShaderFile, const std::string fragmentShaderFile){
    //create the shader program we're going to use
    GLuint program = glCreateProgram();
    GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertexShaderFile);
    GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderFile);

    // connect the shader to the program
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
};


void framebuffer_size_callback(GLFWwindow *window, int width, int height);//Callback function prototype declaration
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

float r = 0.0f; 
float g = 0.0f; 
float b = 0.0f; 

int main() {
    //Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Create a window object
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLFW 3.3.1", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Notify GLFW to set the context of our window as the main context of the current thread
    glfwMakeContextCurrent(window);
    //Register a callback function for the window. Whenever the window changes size, GLFW will call this function and fill in the corresponding parameters for your processing.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //Initialize the function pointer used by GLAD to manage OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    const unsigned char* glVer = glGetString(GL_VERSION);
		std::cout << glVer << std::endl;



    // start with all of the buffers

    float positions[6] = {
        -0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f,
    };


	GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (const void *) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);



    //Initializes the player
    bool game_exit = false;

    //Rendering loop
    while(!glfwWindowShouldClose(window)&&!game_exit) {
		
		
        // input
        processInput(window);

        // Rendering instructions
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);


 
 
        // Check and call event, exchange buffer
        glfwSwapBuffers(window);//Check the trigger event
        glfwPollEvents();    //Exchange color buffer
    }
    //Release/delete all resources allocated before
    glfwTerminate();
    return EXIT_SUCCESS;
}

//Input control, check if the user presses the arrow keys
void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        std::cout<< "Pushed up" <<std::endl;
        r+=0.004;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        std::cout<< "Pushed down" <<std::endl;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        std::cout<< "Pushed left" <<std::endl;
        g+=0.004;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        std::cout<< "Pushed right" <<std::endl;   
        b+=0.004;     
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        std::cout << "Pushed shift" <<std::endl;
        r=g=b=0.0f;
    }
}

// When the user changes the size of the window, the viewport should also be adjusted
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // Note: For Retina display, the width and height will be significantly higher than the original input value.
    glViewport(0, 0, width, height);
}