//
//  ShaderProgram.cpp
//  GKOM_OpenGL_Project
//
//  Created by Piotr Żelazko on 09.12.2017.
//  Copyright © 2017 Piotr Żelazko. All rights reserved.
//

#include "ShaderProgram.hpp"

#include <fstream>
#include <sstream>

using namespace wrench::graphics;

ShaderProgram::ShaderProgram(const std::string &vertexShaderPath,
                             const std::string &fragmentShaderPath):
                                vertexShaderPath_(vertexShaderPath),
                                fragmentShaderPath_(fragmentShaderPath)
{
    linkProgram();
}

GLuint ShaderProgram::compileShader(const std::string& shaderCode,const GLenum& shaderType) {
    
    const GLchar* shaderCodeGL = shaderCode.c_str();
    
    GLuint shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderCodeGL, NULL);
    glCompileShader(shaderID);
    
    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    
    if(!success){
        GLchar infoLog [512];
        glGetShaderInfoLog(shaderID, sizeof(infoLog), NULL, infoLog);
        std::string message = std::string("Shader compilation: ") + infoLog;
        throw std::runtime_error(message);
    }
    
    return shaderID;
}

GLuint ShaderProgram::linkProgram() {
    
    std::pair<GLuint, GLuint> shaders = compileShaders();
    
    GLuint programID = glCreateProgram();
    glAttachShader(programID, shaders.first);
    glAttachShader(programID, shaders.second);
    glLinkProgram(programID);
    
    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success){
        GLchar infoLog [512];
        glGetProgramInfoLog(programID, sizeof(infoLog), nullptr, infoLog);
        std::string message = std::string("Program shaders linking: ") + infoLog;
        throw std::runtime_error(message);
    }
    
    glDeleteShader(shaders.first);
    glDeleteShader(shaders.second);
    
    programID_ = programID;
    
    return programID;
}

GLuint ShaderProgram::getProgramID(){
    return programID_;
}

std::pair<GLuint, GLuint> ShaderProgram::compileShaders() {

    std::string vertexShaderSourceCode   = getShaderSourceCode(vertexShaderPath_);
    std::string fragmentShaderSourceCode = getShaderSourceCode(fragmentShaderPath_);
    
    GLuint vertexShaderID   = compileShader(vertexShaderSourceCode, GL_VERTEX_SHADER);
    GLuint fragmentShaderID = compileShader(fragmentShaderSourceCode, GL_FRAGMENT_SHADER);
    
    return std::make_pair(vertexShaderID, fragmentShaderID);
}

std::string ShaderProgram::getShaderSourceCode(const std::string& shaderPath) {
    
    std::fstream shaderFile;
    shaderFile.exceptions(std::ifstream::badbit);
    
    shaderFile.open(shaderPath);
    if (!shaderFile.is_open())
        throw std::runtime_error("Could not open file: " + shaderPath);
    
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    
    shaderFile.close();
    return shaderStream.str();
}











