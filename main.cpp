#include "glfw.cpp"
#include "opengl.cpp"

#include <iostream>

int main(int argc, char const *argv[])
{
    if(!initGLFW()){
        return -1;
    }

    if(!loadGLAD())
        return -1;

    initOpenGL();

    loopGLFW(&renderOpenGL);

    shutdownGLFW();

    return 0;
}