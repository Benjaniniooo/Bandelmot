#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int windowWidth = 800;
int windowHeight = 600;

GLFWwindow* window;

float lastTime = 0.f;
int framecounter = 0;

void framebufferSizeCallback(GLFWwindow* _window, const int _width, const int _height){
    windowWidth = _width;
    windowHeight = _height;

    glViewport(0, 0, windowWidth, windowHeight);
}

void keyCallback(GLFWwindow* window, const int _key, const int _scancode, const int _action, const int _mode){
    if(_action == GLFW_PRESS && _key == GLFW_KEY_ESCAPE){
        glfwSetWindowShouldClose(window, true);
    }
}

void errorCallback(const int _error, const char* _desc){
    std::cout << "[GLFW ERROR]: " << _error << " " << _desc << std::endl;
}

bool initGLFW(){
    if(!glfwInit()){
        std::cout << "[GLFW ERROR (S)]: glfwInit() failed!" << std::endl; 

        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, "Bandelmot", nullptr, nullptr);
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

void printFPS(){
    if(framecounter < 256){
        framecounter++;
    }else{
        framecounter = 0;

        std::cout << "FPS: " << 256.f / (glfwGetTime() - lastTime) << std::endl;
        lastTime = glfwGetTime();
    }
}

using renderCallbackTypedef = void (*)(void);

void loopGLFW(renderCallbackTypedef renderCallback){
    while(!glfwWindowShouldClose(window)){
        renderCallback();

        printFPS();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}