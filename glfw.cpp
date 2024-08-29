#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int window_width = 800;
int window_height = 600;

GLFWwindow* window;

void framebufferSizeCallback(GLFWwindow* _window, const int _width, const int _height){
    window_width = _width;
    window_height = _height;

    glViewport(0, 0, window_width, window_height);
}

void keyCallback(GLFWwindow* window, const int _key, const int _scancode, const int _action, const int _mode){
    if(_action == GLFW_PRESS && _key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, true);
    }
}

void errorCallback(const int _error, const char* _desc){
    std::cout << "[GLFW ERROR]: " << _error << " " << _desc << std::endl;
}

bool initialiseGLFW(){
    if(!glfwInit()){
        std::cout << "[GLFW ERROR (S)]: glfwInit() failed!" << std::endl; 

        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, "Bandelmot", nullptr, nullptr);
    if(window == nullptr){
        std::cout << "[GLFW ERROR (S)]: glfwCreateWindow() failed!" << std::endl;

        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetErrorCallback(errorCallback);

    return true;
}

bool loadGLAD(){
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "[GLAD ERROR (S)]: gladLoadGLLoader() failed!" << std::endl;

        return false;
    }

    return true;
}

void shutdownGLFW(){
    glfwTerminate();
}

void loopGLFW(){
    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}