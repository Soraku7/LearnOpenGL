//
// Created by Soraku7 on 24-4-27.
//

#ifndef LEARNOPENGL_CAMERA_H
#define LEARNOPENGL_CAMERA_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Tool/Shader.h>
#include <Tool/stb_image.h>
#include <iostream>
class Camera{
public:
    Camera(const glm::vec3 Vector3 = glm::vec3(0.0f , 0.0f , 3.0f));
    
    void mouse_callback(GLFWwindow* window , double xpos , double ypos);
    void scroll_callback(GLFWwindow* window , double xpos , double ypos);
    void processInput(GLFWwindow *window);
    
    bool firstMouse = true;
    
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    //摄像机视野角度
    float fov = 45.0f;
    
    bool isFirstMouse = true;

    // camera
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    
    //鼠标位置
    float lastX = 400, lastY = 300;
    
    float pitch = 0.f , yaw = 0.f;
    //视觉矩阵
    glm::mat4 view;
};


#endif //LEARNOPENGL_CAMERA_H

