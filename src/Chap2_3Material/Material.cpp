//
// Created by Soraku7 on 24-5-26.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Tool/Shader.h>
#include <Tool/Camera.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);
    
    Shader LightingShader("../src/Chap2_3Material/V_MaterialCube.vert" , "../src/Chap2_3Material/F_MaterialCube.frag");
    Shader LightSourceShader("../src/Chap2_1Light/LightingSource.vert" , "../src/Chap2_1Light/LightingSource.frag");
    
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    
    unsigned int VBO , cubeVAO;
    glGenVertexArrays(1 , & cubeVAO);
    glGenBuffers(1 , &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER , VBO);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);
    
    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 6 * sizeof(float) , (void*)0);
    glEnableVertexAttribArray(0);
    
    //法线
    glVertexAttribPointer(1 , 3 , GL_FLOAT , GL_FALSE , 6 * sizeof(float) , (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    
    unsigned int lightCubeVAO;
    glGenVertexArrays(1 , &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER , VBO);
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 6 * sizeof(float) , (void*)0);
    glEnableVertexAttribArray(0);
    
    while(!glfwWindowShouldClose(window)){
        
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        processInput(window);
        
        //刷新缓冲区颜色 背景上色
        glClearColor(0.1f , 0.1f , 0.1f , 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos.y = sin(glfwGetTime() / 2.0f ) * 1.0f;
        
        LightingShader.use();
        LightingShader.setVec3("light.position", lightPos);
        LightingShader.setVec3("viewPos", camera.Position);
        
        glm::vec3 lightColor;
        lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
        lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
        lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        LightingShader.setVec3("light.ambient", ambientColor);
        LightingShader.setVec3("light.diffuse", diffuseColor);
        LightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        

        LightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        LightingShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        LightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        LightingShader.setFloat("material.shininess", 32.0f);
        
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom) , (float)SCR_WIDTH / (float)SCR_HEIGHT , 0.1f , 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        LightingShader.setMat4("projection" , projection);
        LightingShader.setMat4("view" , view);
        
        glm::mat4 model = glm::mat4(1.0f);
        LightingShader.setMat4("model" , model);
        
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES , 0 , 36);
        
        
        LightSourceShader.use();
        LightSourceShader.setMat4("projection" , projection);
        LightSourceShader.setMat4("view" , view);
        model = glm::mat4(1.0f);
        model = glm::translate(model , lightPos);
        model = glm::scale(model , glm::vec3(0.2f));
        LightSourceShader.setMat4("model" , model);
        
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES , 0 , 36);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    glDeleteVertexArrays(1 , &cubeVAO);
    glDeleteVertexArrays(1 , &lightCubeVAO);
    glDeleteBuffers(1 , &VBO);
    glfwTerminate();
    
    return 0;
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}