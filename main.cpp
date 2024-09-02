#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

GLFWwindow* window;

int windowWidth = 800,
    windowHeight = 600;

float lastTime = 0.f;
int framecounter = 0;

void errorCallback(const int errorCode, const char* errorDescription){
    std::cout << "[GLFW ERROR]: " << errorCode << " " << errorDescription << std::endl;
}

void framebufferSizeCallback(GLFWwindow* pWindow, const int pWidth, const int pHeight){
    windowWidth = pWidth;
    windowHeight = pHeight;

    glViewport(0, 0, windowWidth, windowHeight);
}

void keyCallback(GLFWwindow* pWindow, const int pKey, const int pScanCode, const int pAction, const int pMode){
    if(pAction == GLFW_PRESS){
        if(pKey == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, true);
        }
    }
}

int main(int argc, char const *argv[])
{
    glfwSetErrorCallback(errorCallback);

    if(!glfwInit()){
        std::cout << "[GLFW ERROR S]: glfwInit() failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, "ImGui Test", nullptr, nullptr);
    if(!window){
        std::cout << "[GLFW ERROR S]: glfwCreateWindow() failed!" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);    // 0 = no VSYNC, 1 = VSYNC

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "[GLAD ERROR S]: gladLoadGLLoader() failed!" << std::endl;
        return -1;
    }

    ////////////////

    ImGui::CreateContext();

    if(!ImGui_ImplGlfw_InitForOpenGL(window, true)){
        std::cout << "[IMGUI ERROR S]: ImGui_ImplGlfw_InitForOpenGL() failed!" << std::endl;
        return -1;
    }
    if(!ImGui_ImplOpenGL3_Init()){
        std::cout << "[IMGUI ERROR S]: ImGui_ImplOpenGL3_Init() failed!" << std::endl;
        return -1;
    }

    ////////////////

    while(!glfwWindowShouldClose(window)){
        if(framecounter < 256){
            framecounter++;
        }else{
            framecounter = 0;

            std::cout << "FPS: " << 256.f / (glfwGetTime() - lastTime) << std::endl;
            lastTime = glfwGetTime();
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}