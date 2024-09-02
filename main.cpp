#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "shader.hpp"

////////////////

GLFWwindow* window;

int windowWidth = 800,
    windowHeight = 600;

float lastTime = 0.f;
int framecounter = 0;

////////////////

GLuint VAO, VBO, EBO;
GLuint vertexShader, fragmentShader, shaderProgram;

GLint success;
char info[512];

////////////////

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

////////////////

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

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderProg, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, info);
        std::cout << "[OPENGL ERROR S]: glCompileShader(vertexShader) failed!: " << std::endl;
        std::cout << info << std::endl;
        return -1;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderProg, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, info);
        std::cout << "[OPENGL ERROR S]: glCompileShader(fragmentShader) failed!:" << std::endl;
        std::cout << info << std::endl;
        return -1;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
        std::cout << "[OPENGL ERROR S]: glLinkProgram(shaderProgram) failed!:" << std::endl;
        std::cout << info << std::endl;
        return -1;
    }

    glValidateProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
        std::cout << "[OPENGL ERROR S]: glValidateProgram(shaderProgram) failed!:" << std::endl;
        std::cout << info << std::endl;
        return -1;
    }

    glUseProgram(shaderProgram);

    //--------------

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) 0);
    glEnableVertexAttribArray(0);

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

        ////////////////

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ////////////////

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ////////////////

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