#include "Tool/Shader.h"
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    //failbit 可恢复错误  badbit 系统级错误
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream ::badbit);
    fShaderFile.exceptions(std::ifstream ::failbit | std::ifstream ::badbit);
    
    try{
        //打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream , fShaderStream;
        
        //读取文件的缓冲内容到数据流
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        //关闭文件处理
        vShaderFile.close();
        fShaderFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
    }
    catch (std::ifstream ::failure &e ){
        std:: cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << e.what() << std::endl;
    }
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    unsigned int vertex , fragment;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex , 1 , &vShaderCode , NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    

}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID , name.c_str()) , (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID , name.c_str()) , value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID , name.c_str()) , value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID , name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec3) const
{
    glUniform3fv(glGetUniformLocation(ID , name.c_str()) , 1 , &vec3[0]);
}


void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID , name.c_str()) , x , y , z);
}


void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}



