#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

unsigned int WINDOW_WIDTH = 800;
unsigned int WINDOW_HEIGHT = 600;

float lastTime = 0.f;
unsigned int framecounter = 0;

void resize_callback(GLFWwindow* window, int width, int height)
{
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        if(key == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, true);
        }
        if(key == GLFW_KEY_V){
            glfwSwapInterval(0);
        }
    }
}

void error_callback(int error, const char* description){
    printf("[GLFW ERROR %d]: %s\n", error, description);
}

int main(int argc, char const *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bandelmot", NULL, NULL);
    if(window == NULL){
        glfwTerminate();
        std::cout << "Could not create GLFW window!" << std::endl;

        return -1;
    }
    
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSetKeyCallback(window, input_callback);
    glfwSetErrorCallback(error_callback);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialise GLAD!" << std::endl;

        return -1;
    }

    while(!glfwWindowShouldClose(window)){
        if(framecounter < 100){
            framecounter++;
        }else{
            framecounter = 0;
            
            std::cout << "FPS: " << 100.f / (glfwGetTime() - lastTime) << std::endl;
            lastTime = glfwGetTime();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

