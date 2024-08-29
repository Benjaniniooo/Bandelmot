#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

unsigned int WINDOW_WIDTH = 800;
unsigned int WINDOW_HEIGHT = 600;

void resize_callback(GLFWwindow* window, int width, int height)
{
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void inputHandler(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
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

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialise GLAD!" << std::endl;

        return -1;
    }

    while(!glfwWindowShouldClose(window)){
        inputHandler(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

