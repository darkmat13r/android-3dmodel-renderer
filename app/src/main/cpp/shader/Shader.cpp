//
// Created by Dark Matter on 5/18/24.
//

#include "Shader.h"
#include "AndroidOut.h"
#include "gtc/type_ptr.hpp"
#include "utils.h"
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
        materialLoc.samplerSpecularExponentLocation = glGetUniformLocation(program_,
                                                                           "uSpecTexture");
        materialLoc.specularColor = glGetUniformLocation(program_, "uMaterial.specularColor");
        cameraLocalPosLocation_ = glGetUniformLocation(program_, "uCameraLocalPos");
        numberOfPointLightLocation_ = glGetUniformLocation(program_, "uNumOfLights");

        for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(pointLightLocation); ++i) {
            char name[128];
            memset(name, 0, sizeof(name));
            SNPRINTF(name, sizeof(name), "uPointLights[%d].light.color", i);
            pointLightLocation[i].color = glGetUniformLocation(program_, name);

            SNPRINTF(name, sizeof(name), "uPointLights[%d].light.ambientIntensity", i);
            pointLightLocation[i].ambientIntensity = glGetUniformLocation(program_, name);

            SNPRINTF(name, sizeof(name), "uPointLights[%d].localPos", i);
            pointLightLocation[i].localPosition = glGetUniformLocation(program_, name);

            SNPRINTF(name, sizeof(name), "uPointLights[%d].light.diffuseIntensity", i);
            pointLightLocation[i].diffuseIntensity = glGetUniformLocation(program_, name);

            SNPRINTF(name, sizeof(name), "uPointLights[%d].atten.constant", i);
            pointLightLocation[i].attenuation.constant = glGetUniformLocation(program_, name);

            SNPRINTF(name, sizeof(name), "uPointLights[%d].atten.linear", i);
            pointLightLocation[i].attenuation.linear = glGetUniformLocation(program_, name);

            SNPRINTF(name, sizeof(name), "uPointLights[%d].atten.exp", i);
            pointLightLocation[i].attenuation.exp = glGetUniformLocation(program_, name);

            if (
                    pointLightLocation[i].color == INVALID_UNIFORM_LOCATION ||
                    pointLightLocation[i].ambientIntensity == INVALID_UNIFORM_LOCATION ||
                    pointLightLocation[i].localPosition == INVALID_UNIFORM_LOCATION ||
                    pointLightLocation[i].diffuseIntensity == INVALID_UNIFORM_LOCATION ||
                    pointLightLocation[i].attenuation.constant == INVALID_UNIFORM_LOCATION ||
                    pointLightLocation[i].attenuation.linear == INVALID_UNIFORM_LOCATION ||
                    pointLightLocation[i].attenuation.exp == INVALID_UNIFORM_LOCATION
                    ) {
                glDeleteProgram(program_);
            }
        }
        if (projectionMatrixLocation_ == INVALID_UNIFORM_LOCATION
            || positionAttribute_ == INVALID_UNIFORM_LOCATION
            || materialLoc.useDiffText_ == INVALID_UNIFORM_LOCATION
            || materialLoc.diffuseColor == INVALID_UNIFORM_LOCATION
            || uvAttribute_ == INVALID_UNIFORM_LOCATION) {
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

void Shader::setProjectionMatrix(const Mat4f *projectionMatrix) const {
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



