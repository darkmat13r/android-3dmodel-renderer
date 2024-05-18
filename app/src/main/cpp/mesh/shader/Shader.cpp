//
// Created by Dark Matter on 5/18/24.
//

#include "Shader.h"
#include "AndroidOut.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(std::string& vertexShaderPath, std::string& fragmentShaderPath) {
    program_ = glCreateProgram();
    std::string vertexShaderSource = readFile(vertexShaderPath);
    std::string fragmentShaderSource = readFile(fragmentShaderPath);

    GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    glAttachShader(program_, vertexShader);
    glAttachShader(program_, vertexShader);

    GLint  success;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetProgramInfoLog(program_, 512, nullptr, infoLog);
        aout << "ERROR: Shader program linking failed. : " << infoLog << std::endl;
        glDeleteProgram(program_);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    projectionMatrixLocation_ = glGetUniformLocation(program_, "uProjection");
    positionAttribute_ = glGetUniformLocation(program_, "uPosition");
    uvAttribute_ = glGetUniformLocation(program_, "uPosition");
}

GLuint Shader::compileShader(std::string &shaderCode, GLenum shaderType) {
    auto shader = glCreateShader(shaderType);
    const char *source = shaderCode.c_str();
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        aout << "ERROR: Shader compilation failed. : " << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

std::string Shader::readFile(std::string &fileName) const {
    std::ifstream shaderFile;
    shaderFile.open(fileName);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}


void Shader::bind() {
    glUseProgram(program_);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::setProjectionMatrix(const Mat4f *projectionMatrix) {
    glUniformMatrix4fv(projectionMatrixLocation_, 1, GL_TRUE, &projectionMatrix->m[0][0]);
}

