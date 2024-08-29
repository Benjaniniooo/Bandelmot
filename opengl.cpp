#pragma once

#include <glad/glad.h>

#include <iostream>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

const char* vertexShaderProg = R"(
#version 460 core
layout (location = 0) in vec3 pos;

void main(){
    gl_Position = vec4(pos, 1.0);
}
)";

const char* fragmentShaderProg = R"(
#version 460 core
out vec4 color;

void main(){
    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

GLuint vertexShader, fragmentShader;
GLuint shaderProgram;

GLuint VAO, VBO;

GLint success;
char info[512];

void initOpenGL(){
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderProg, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, info);
        std::cout << "[OPENGL ERROR]: Compilation of vertex shader failed!: " << info << std::endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderProg, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, info);
        std::cout << "[OPENGL ERROR]: Compilation of fragment shader failed!: " << info << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
        std::cout << "[OPENGL ERROR]: Linking of shader program failed!: " << info << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
}

void renderOpenGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}