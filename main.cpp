#include "glfw.cpp"

#include <iostream>

int main(int argc, char const *argv[])
{
    if(!initialiseGLFW()){
        return -1;
    }

    if(!loadGLAD())
        return -1;

    glfwLoop();

    shutdownGLFW();

    return 0;
}