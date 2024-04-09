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
                                 "out vec4 vertexColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos , 1.0);\n"
                                 "   vertexColor = vec4(0.5 , 0.0 , 0.0 , 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec4 vertexColor;"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vertexColor;\n"
                                   "}\n\0";


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
    
    //顶点坐标
    float vertices[] = {
            -0.5f , -0.5f , 0.0f,
            0.5f , -0.5f , 0.0f,
            0.0f , 0.5f , 0.0f
    };
    
    
    //生成OpenGL对象
    unsigned int VBO;
    unsigned int VAO;
    
    glGenBuffers(1 , &VBO);
    glGenVertexArrays(1 , &VAO);
    
    glBindVertexArray(VAO);
    
    //顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
    //将创建的缓冲绑定到GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER , VBO);
    
    
    //将顶点复制到缓冲内存
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);
    
    //创建顶点着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    //着色器源码附加到着色器上
    //1.参数为着色器对象 2.传递源码的字符串数量 3.顶点着色器最终源码
    glShaderSource(vertexShader , 1 , &vertexShaderSource , NULL);
    glCompileShader(vertexShader);
    
    //创建片元着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader , 1 , &fragmentShaderSource , NULL);
    glCompileShader(fragmentShader);
    
    //创建着色器程序 对前面的步骤进行链接
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    //将着色器附加到程序上
    glAttachShader(shaderProgram , vertexShader);
    glAttachShader(shaderProgram , fragmentShader);
    glLinkProgram(shaderProgram);
    
    //测试
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    //调用后删除对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //告诉GLSL如何解析顶点数据
    //1.将layout(location=0)的位置属性通知每个顶点
    //2.顶点属性的大小 顶点是vec3 所以值是3  3.数据传入类型
    //4.数据是否被标准化 映射到0-1之间 5.步长 指连续顶点属性组之间的距离 这里是3个float
    //6.缓冲位置的起始偏移量 位置位于数组的开头 则偏移量为0
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof(float) , (void*)0);
    glEnableVertexAttribArray(0);
    
    
    //重复渲染
    while (!glfwWindowShouldClose(window))
    {
        //输入
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES , 0 , 3);
        
        
        //渲染 交换缓冲
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
