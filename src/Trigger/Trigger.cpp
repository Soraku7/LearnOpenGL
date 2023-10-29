#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    //顶点坐标
    float vertices[] = {
            -0.5f , -0.5f , 0.0f,
            0.5f , -0.5f , 0.0f,
            0.0f , 0.5f , 0.0f
    };


    //生成OpenGL对象
    unsigned int VBO;
    glGenBuffers(1 , &VBO);

    //顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
    //将创建的缓冲绑定到GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER , VBO);

    //将顶点复制到缓冲内存
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

    return 0;
}

