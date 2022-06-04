// // System Headers
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// #include <iostream>




// void framebuffer_size_callback(GLFWwindow *window, int width, int height);//Callback function prototype declaration
// void processInput(GLFWwindow *window);

// // settings
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 800;

// int main() {
//     //Initialize GLFW
//     GLFWwindow *window;
//     if(!glfwInit())
//         return -1;

//     window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLFW 3.3.1", NULL, NULL);
//     if(!window){
//         glfwTerminate();
//         return -1;
//     }
    
//     //Notify GLFW to set the context of our window as the main context of the current thread
//     glfwMakeContextCurrent(window);
//     //Register a callback function for the window. Whenever the window changes size, GLFW will call this function and fill in the corresponding parameters for your processing.
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//     //Initialize the function pointer used by GLAD to manage OpenGL
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         std::cout << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

//     const unsigned char* glVer = glGetString(GL_VERSION);
// 		std::cout << glVer << std::endl;



//     // start with all of the buffers

//     float positions[6] = {
//         -0.5f, 0.5f,
//         -0.5f, -0.5f,
//         0.5f, -0.5f,
//     };


// 	GLuint indexBufferObject;
//     glGenBuffers(1, &indexBufferObject);
//     glBindBuffer(GL_ARRAY_BUFFER, indexBufferObject);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);


//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (const void *) 0);



//     //use the shader
//     GLuint shader = createShader("../resources/shaders/vertexShader.glsl", "../resources/shaders/fragmentShader.glsl");
//     glUseProgram(shader);


//     //Initializes the player
//     bool game_exit = false;

//     //Rendering loop
//     while(!glfwWindowShouldClose(window)&&!game_exit) {
//         // Rendering instructions

//         glClear(GL_COLOR_BUFFER_BIT);
//         // Check and call event, exchange buffer
//         glfwSwapBuffers(window);//Check the trigger event
//         glfwPollEvents();    //Exchange color buffer

 
//         // input
//         processInput(window);
 
//     }
//     //Release/delete all resources allocated before
//     glfwTerminate();
//     return EXIT_SUCCESS;
// }



// // When the user changes the size of the window, the viewport should also be adjusted
// void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
//     // Note: For Retina display, the width and height will be significantly higher than the original input value.
//     glViewport(0, 0, width, height);
// }
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";



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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = createShader("../resources/shaders/vertexShader.glsl", "../resources/shaders/fragmentShader.glsl");
    
    //glCreateProgram();
    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
     }
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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


