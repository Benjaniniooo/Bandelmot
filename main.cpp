#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

unsigned int WINDOW_WIDTH = 800;
unsigned int WINDOW_HEIGHT = 600;

float lastTime = 0.f;
unsigned int framecounter = 0;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

const char *vertexShaderGLSL = 
"#version 460 core\n"
"layout (location = 0) in vec3 pos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(pos, 1.0);\n"
"}\n";

const char *fragmentShaderGLSL = 
"#version 460 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";


void resize_callback(GLFWwindow* window, int width, int height){
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

int main(int argc, char const *argv[]){
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

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderGLSL, NULL);
    glCompileShader(vertexShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION: " << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderGLSL, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION: " << infoLog << std::endl;
    }

    unsigned int shaderProg = glCreateProgram();
    glAttachShader(shaderProg, vertexShader);
    glAttachShader(shaderProg, fragmentShader);
    glLinkProgram(shaderProg);

    glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProg, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::PROGRAM::LINKING: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)){
        if(framecounter < 100){
            framecounter++;
        }else{
            framecounter = 0;
            
            std::cout << "FPS: " << 100.f / (glfwGetTime() - lastTime) << std::endl;
            lastTime = glfwGetTime();
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProg);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

