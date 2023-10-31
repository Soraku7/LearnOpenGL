//
// Created by Soraku7 on 2023/10/31.
//
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

//随着窗体大小更变
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//读取输入
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0, 1, 0, 1.0f);\n"
                                   "}\n\0";


int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window= glfwCreateWindow(SCR_WIDTH , SCR_HEIGHT , "LearnOpenGL" , NULL , NULL);
    
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window , framebuffer_size_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    
    float vertex[] ={
        0.5f , 0 , 0 ,
        -0.5 , 0 , 0,
        0 , 0.5f , 0,
        0 , -0.5f , 0
    };
    
    unsigned int indices[]={
        0 , 1 , 2,
        0 , 1, 3
    };
    
    unsigned int VAO , VBO , EBO;
    
    glGenVertexArrays(1 , &VAO);
    glGenBuffers(1 , &VBO);
    glGenBuffers(1 , &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER , VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , EBO);
    
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertex) , vertex , GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(indices) , indices , GL_STATIC_DRAW);
    
    unsigned int vertexShader;
    vertexShader =glCreateShader(vertexShader);
    
    glShaderSource(vertexShader , 1 , &vertexShaderSource , NULL);
    glCompileShader(vertexShader);
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader , 1 , &fragmentShaderSource , NULL);
    glCompileShader(fragmentShader);
    
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram , vertexShader);
    glAttachShader(shaderProgram , fragmentShader);
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3* sizeof(float) , (void*)0);
    glEnableVertexAttribArray(0);
    
    while(!glfwWindowShouldClose(window)){
        
        processInput(window);
        
        glClearColor(0.2f , 0.3f , 0.3f , 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        
        glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0);
        //glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        
    }
    
    glDeleteVertexArrays(1 , &VAO);
    glDeleteBuffers(1 , &VBO);
    glDeleteProgram(shaderProgram);
    
    glfwTerminate();
    
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
    //按下ESC关闭窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
