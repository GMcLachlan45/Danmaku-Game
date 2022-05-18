#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
    public:
        GLFWwindow *window;

        Renderer();
        ~Renderer();

        void initialize();
        bool window_fails();
        void render();
};
