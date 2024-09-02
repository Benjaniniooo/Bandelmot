#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f, // bottom left
    -1.0f, 1.0f, 0.0f,  // top left
    1.0f, 1.0f, 0.0f,   // top right
    1.0f, -1.0f, 0.0f,  // bottom right
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};

const char* vertexShaderProg = R"(
#version 460 core
layout (location = 0) in vec3 pos;

out vec2 positionVertex;

void main(){
    gl_Position = vec4(pos, 1.0);
    positionVertex = pos.xy;
}
)";

const char* fragmentShaderProg = R"(
#version 460 core
in vec2 positionVertex;

out vec4 color;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main(){
    vec2 c = vec2(
        map(positionVertex.x, -1.0, 1.0, -2.0, 1.0),
        map(positionVertex.y, -1.0, 1.0, -2.0, 2.0)
        );

    vec2 z = vec2(0.0, 0.0);

    uint iterationMax = 500;

    uint iteration = 0;

    while(length(z) <= 8 && iteration < iterationMax){
        z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y);
        z = z + c;

        iteration = iteration + 1;
    }

    float grad = map(iteration, 0, iterationMax, 0.0, 1.0);

    color = vec4(grad, 0.0, 0.0, 1.0);
}
)";

GLuint vertexShader, fragmentShader;
GLuint shaderProgram;

GLuint VAO, VBO, EBO;

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

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
        std::cout << "[OPENGL ERROR]: Validation of shader program failed!: " << info << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    
    glEnableVertexAttribArray(0);
    glUseProgram(shaderProgram);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void renderOpenGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}