#define STB_IMAGE_IMPLEMENTATION
#include "Tool/stb_image.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Tool/Shader.h"
#include <iostream>

//随着窗体大小更变
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//读取输入
void processInput(GLFWwindow *window);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    Shader ourShader("D:\\LearnOpenGL\\src\\Texture\\Assets\\TextureVertex.vert" , "D:\\LearnOpenGL\\src\\Texture\\Assets\\TextureFragment.frag");
    
    //顶点坐标
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    
    //使用EBO(Element Buffer Object)对绘制三角形设置顺序
    unsigned int indices[]={
            0 , 1 , 3,
            1 , 2 , 3
    };
    
    //生成OpenGL对象
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    
    glGenBuffers(1 , &VBO);
    glGenVertexArrays(1 , &VAO);
    glGenBuffers(1 , &EBO);
    
    glBindVertexArray(VAO);
    
    //顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
    //将创建的缓冲绑定到GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER , VBO);
    //元素缓冲对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , EBO);
    
    //将顶点复制到缓冲内存
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(indices) , indices , GL_STATIC_DRAW);
    
    //告诉GLSL如何解析顶点数据
    //1.将layout(location=0)的位置属性通知每个顶点
    //2.顶点属性的大小 顶点是vec3 所以值是3  3.数据传入类型
    //4.数据是否被标准化 映射到0-1之间 5.步长 指连续顶点属性组之间的距离 这里是3个float
    //6.缓冲位置的起始偏移量 位置位于数组的开头 则偏移量为0
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 8 * sizeof(float) , (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1 , 3 , GL_FLOAT , GL_FALSE , 8 * sizeof(float) , (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2 , 2 , GL_FLOAT , GL_FALSE , 8 * sizeof(float) , (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    unsigned int texture;
    glGenTextures(1 , &texture);
    glBindTexture(GL_TEXTURE_2D , texture);
    
    //绑定坐标轴
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT);
    //设置高低通滤波的过滤方式
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
    
    //长 宽 颜色 三个通道
    int width , height , nrChannel;
    unsigned char *data = stbi_load("D:\\LearnOpenGL\\src\\Texture\\Assets\\container.jpg" ,
                            &width , &height , &nrChannel , 0);
    
    if (data)
    {
        //1.纹理目标 2.Mipmap 级别 0为标准级别 3.期望图像的存储格式RGBA 4、5 为宽高
        //7.图源格式 8.数据类型 9.图像数据
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    ourShader.use();
    
    //重复渲染
    while (!glfwWindowShouldClose(window))
    {
        //输入
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES , 0 , 3);
        //1.绘制模式 2.绘制的点数量 3.索引类型 4.偏移值
        glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0);
        //线框模式绘制
        //1.康到三角形的正面和背面 2.用线绘制
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //渲染 交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
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
