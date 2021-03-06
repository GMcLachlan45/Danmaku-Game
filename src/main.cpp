#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <string>
#include <fstream>

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



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

float r = 0.0f; 
float g = 0.0f; 
float b = 0.0f; 


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Danmaku Game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // link shaders
    GLuint shaderProgram = createShader("../resources/shaders/vertexShader.glsl", "../resources/shaders/fragmentShader.glsl");
    
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        std::cout << "ISSUE ATTATCHING THE SHADER TO THE PROGRAM\n"  << std::endl;
    }
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // bottom left  0
         0.5f, -0.5f, 0.0f, // bottom right  `1
         0.5f,  0.5f, 0.0f, // top right2
        -0.5f,  0.5f, 0.0f  // top left do this stuff ahaahhahahahahahhahah     3
    }; 

    unsigned indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // holy moly, that's cool
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH/ (float) SCR_HEIGHT, -0.4f, 5.0f);

    std::cout << glm::to_string(proj) << std::endl;


    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, //layout location  
                          3, // number of values we pass in
                          GL_FLOAT, //value type
                          GL_FALSE, // is this normalized
                          3 * sizeof(float), // how many bytes it is between vertex elements
                          (void*)0); // how many bytes it is until the first element 
    glEnableVertexAttribArray(0);

    GLuint IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);






    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  //  glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // initialize the player and game variables
    bool game_exit = false;
    const unsigned char* glVer = glGetString(GL_VERSION);
		std::cout << "Currently using " << glVer << std::endl;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)&&!game_exit)
    {
        // input
        processInput(window);

        // render
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}