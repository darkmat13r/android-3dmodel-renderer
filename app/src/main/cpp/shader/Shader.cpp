//
// Created by Dark Matter on 5/18/24.
//

#include "Shader.h"
#include "AndroidOut.h"
#include "gtc/type_ptr.hpp"
#include <shader/Shaders.h>
#include <fstream>
#include <sstream>
#include <iostream>


Shader::Shader(std::string &vertexShaderPath, std::string &fragmentShaderPath) {
    program_ = glCreateProgram();
    GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    glAttachShader(program_, vertexShader);
    glAttachShader(program_, fragmentShader);

    glLinkProgram(program_);

    GLint success;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength = 0;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &logLength);

        // If we fail to link the shader program, log the result for debugging
        if (logLength) {
            GLchar *log = new GLchar[logLength];
            glGetProgramInfoLog(program_, logLength, nullptr, log);
            aout << "Failed to link program with:\n" << log << std::endl;
            delete[] log;
        }
        glDeleteProgram(program_);
    } else {
        projectionMatrixLocation_ = glGetUniformLocation(program_, "uProjection");
        materialLoc.diffuseColor = glGetUniformLocation(program_, "uMaterial.diffuseColor");
        materialLoc.useDiffText_ = glGetUniformLocation(program_, "uMaterial.useTexture");
        materialLoc.ambientColor = glGetUniformLocation(program_, "uMaterial.ambientColor");
        lightLoc.color = glGetUniformLocation(program_, "uLight.light.color");
        lightLoc.ambientIntensity = glGetUniformLocation(program_, "uLight.light.ambientIntensity");
        lightLoc.diffuseIntensity = glGetUniformLocation(program_, "uLight.light.diffuseIntensity");
        lightLoc.direction = glGetUniformLocation(program_, "uLight.direction");
        lightTypeLocation = glGetUniformLocation(program_, "uLight.light.type");
        positionAttribute_ = glGetAttribLocation(program_, "inPosition");
        normalAttribute = glGetAttribLocation(program_, "inNormal");
        uvAttribute_ = glGetAttribLocation(program_, "inUV");
        materialLoc.samplerSpecularExponentLocation = glGetUniformLocation(program_, "uSpecTexture");
        materialLoc.specularColor = glGetUniformLocation(program_, "uMaterial.specularColor");
        cameraLocalPosLocation_ = glGetUniformLocation(program_, "uCameraLocalPos");
        numberOfPointLightLocation_ = glGetUniformLocation(program_, "uNumOfLights");

        if (projectionMatrixLocation_ == -1
            || positionAttribute_ == -1
            || materialLoc.useDiffText_ == -1
            || materialLoc.diffuseColor == -1
            || uvAttribute_ == -1) {
            glDeleteProgram(program_);
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

GLint Shader::getPositionAttrib() const {
    return positionAttribute_;
}

GLint Shader::getUvAttrib() const {
    return uvAttribute_;
}

GLuint Shader::compileShader(const char *shaderCode, GLenum shaderType) {
    auto shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
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


void Shader::bind() const {
    glUseProgram(program_);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::setProjectionMatrix(const Mat4f *projectionMatrix) const{
    glUniformMatrix4fv(projectionMatrixLocation_, 1, GL_TRUE, &projectionMatrix->m[0][0]);
}

GLint Shader::getDiffColorLocation() const {
    return materialLoc.diffuseColor;
}

GLint Shader::getAmbientColorLocation() const {
    return materialLoc.ambientColor;
}

GLint Shader::getUseDiffTextureLocation() const {
    return materialLoc.useDiffText_;
}

GLint Shader::getLightColorLocation() const {
    return lightLoc.color;
}

GLint Shader::getAmbientIntensityLocation() const {
    return lightLoc.ambientIntensity;
}

GLint Shader::getSpecularExponentLocation() const {
    return materialLoc.samplerSpecularExponentLocation;
}

GLint Shader::getSpecularColorLocation() const {
    return materialLoc.specularColor;
}

GLint Shader::getCameraLocalPosLocation() const {
    return cameraLocalPosLocation_;
}

GLint Shader::getLightDirectionLocation() const {
    return lightLoc.direction;
}

GLint Shader::getDiffuseIntensityLocation() const {
    return lightLoc.diffuseIntensity;
}



