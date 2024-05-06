//
// Created by Soraku7 on 24-5-6.
//
#include<Tool/Camera.h>
Camera::Camera(const glm::vec3) {
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::mouse_callback(GLFWwindow* window , double xpos , double ypos){
    
    if(isFirstMouse){
        lastX = xpos;
        lastY = ypos;
        isFirstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    //鼠标灵敏度
    float sensitivity = 0.01f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    
    if(pitch > 89.0f){
        pitch = 89.0;
    }
    if(yaw < -89.0f){
        yaw = -89.0;
    }
    
    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(pitch)) * sin(glm::radians(yaw));
    
    cameraFront = glm::normalize(front);
}

void Camera::scroll_callback(GLFWwindow* window , double xoffset , double yoffset){
    if(fov >= 1.0f && fov <= 45.0f){
        fov -= yoffset;
    }
    if(fov <= 1.0f) fov = 1.0f;
    if(fov >= 45.0f) fov = 45.0f;
}

void Camera::processInput(GLFWwindow *window)
{
    //按下ESC关闭窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    float cameraSpeed = 2.5f * deltaTime;
    if(glfwGetKey(window , GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if(glfwGetKey(window , GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if(glfwGetKey(window , GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront , cameraUp)) * cameraSpeed;
    if(glfwGetKey(window , GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront , cameraUp)) * cameraSpeed;
}