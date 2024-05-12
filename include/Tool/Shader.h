#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include "glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
public:
    unsigned int ID;
    
    //构造函数构建着色器
    Shader(const char* vertexPath , const char* fragmentPath);
    
    void use();
    
    void setBool(const std::string &name , bool value) const;
    void setInt(const std::string &name , int value) const;
    void setFloat(const std::string &name , float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setVec3(const std::string &name , const glm::vec3 &vec3)const;
    void setVec3(const std::string &name , float x , float y , float z)const;
private:
   
    void checkCompileErrors(unsigned int shader, std::string type);
};


#endif //LEARNOPENGL_SHADER_H
