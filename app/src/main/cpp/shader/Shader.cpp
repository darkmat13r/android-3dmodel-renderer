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
#include <string.h>
#include <stdio.h>


Shader::Shader() {
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
        numberOfSpotLightLocation_ = glGetUniformLocation(program_, "uNumOfSpotLights");

        loadPointLightUniforms();

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

void Shader::loadSpotLightUniforms() {
    for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(spotLightLocation); ++i) {
        char name[128];
        memset(name, 0, sizeof(name));
        SNPRINTF(name, sizeof(name), "uSpotLights[%d].light.color", i);
        spotLightLocation[i].color = glGetUniformLocation(program_, name);

        SNPRINTF(name, sizeof(name), "uSpotLights[%d].light.ambientIntensity", i);
        spotLightLocation[i].ambientIntensity = glGetUniformLocation(program_, name);

        SNPRINTF(name, sizeof(name), "uSpotLights[%d].localPos", i);
        spotLightLocation[i].localPosition = glGetUniformLocation(program_, name);

        SNPRINTF(name, sizeof(name), "uSpotLights[%d].light.diffuseIntensity", i);
        spotLightLocation[i].diffuseIntensity = glGetUniformLocation(program_, name);

        SNPRINTF(name, sizeof(name), "uSpotLights[%d].atten.constant", i);
        spotLightLocation[i].attenuation.constant = glGetUniformLocation(program_, name);

        SNPRINTF(name, sizeof(name), "uSpotLights[%d].atten.linear", i);
        spotLightLocation[i].attenuation.linear = glGetUniformLocation(program_, name);

        SNPRINTF(name, sizeof(name), "uSpotLights[%d].atten.exp", i);
        spotLightLocation[i].attenuation.exp = glGetUniformLocation(program_, name);

        SNPRINTF(name, sizeof(name), "uSpotLights[%d].direction", i);
        spotLightLocation[i].direction = glGetUniformLocation(program_, name);

        SNPRINTF(name, sizeof(name), "uSpotLights[%d].cutOff", i);
        spotLightLocation[i].cutOff = glGetUniformLocation(program_, name);

        if (
                spotLightLocation[i].color == INVALID_UNIFORM_LOCATION ||
                spotLightLocation[i].ambientIntensity == INVALID_UNIFORM_LOCATION ||
                spotLightLocation[i].localPosition == INVALID_UNIFORM_LOCATION ||
                spotLightLocation[i].diffuseIntensity == INVALID_UNIFORM_LOCATION ||
                spotLightLocation[i].attenuation.constant == INVALID_UNIFORM_LOCATION ||
                spotLightLocation[i].attenuation.linear == INVALID_UNIFORM_LOCATION ||
                spotLightLocation[i].attenuation.exp == INVALID_UNIFORM_LOCATION
                ) {
            glDeleteProgram(program_);
        }
    }
}

void Shader::loadPointLightUniforms() {
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

bool Shader::isValidIndex(int index) const {
    if (index >= 0 && index < MAX_POINT_LIGHTS) {
        return true;
    } else {
        std::cerr << "Index out of bounds: " << index << std::endl;
        return false;
    }
}

GLint Shader::getPointLightColor(int index) const {
    if (isValidIndex(index)) {
        return pointLightLocation[index].color;
    } else {
        return -1; // or appropriate error value
    }
}

GLint Shader::getPointLightAmbientIntensity(int index) const {
    if (isValidIndex(index)) {
        return pointLightLocation[index].ambientIntensity;
    } else {
        return -1; // or appropriate error value
    }
}

GLint Shader::getPointLightDiffuseIntensity(int index) const {
    if (isValidIndex(index)) {
        return pointLightLocation[index].diffuseIntensity;
    } else {
        return -1; // or appropriate error value
    }
}


GLint Shader::getPointLightLocalPosition(int index) const {
    if (isValidIndex(index)) {
        return pointLightLocation[index].localPosition;
    } else {
        return -1; // or appropriate error value
    }
}

GLint Shader::getPointLightAttenuationConstant(int index) const {
    if (isValidIndex(index)) {
        return pointLightLocation[index].attenuation.constant;
    } else {
        return 0; // or appropriate error value
    }
}

GLint Shader::getPointLightAttenuationLinear(int index) const {
    if (isValidIndex(index)) {
        return pointLightLocation[index].attenuation.linear;
    } else {
        return 0; // or appropriate error value
    }
}

GLint Shader::getPointLightAttenuationExp(int index) const {
    if (isValidIndex(index)) {
        return pointLightLocation[index].attenuation.exp;
    } else {
        return 0; // or appropriate error value
    }
}

GLint Shader::getNumberOfLightsLocation() const {
    return numberOfPointLightLocation_;
}

GLint Shader::getNumberOfSpotLightsLocation() const {
    return numberOfSpotLightLocation_;
}

GLint Shader::getSpotLightColor(int index) const {
    return spotLightLocation->color;
}

GLint Shader::getSpotLightAmbientIntensity(int index) const {
    return spotLightLocation->ambientIntensity;
}

GLint Shader::getSpotLightDiffuseIntensity(int index) const {
    return spotLightLocation->diffuseIntensity;
}

GLint Shader::getSpotLightLocalPosition(int index) const {
    return spotLightLocation->localPosition;
}

GLint Shader::getSpotLightAttenuationConstant(int index) const {
    return spotLightLocation->attenuation.constant;
}

GLint Shader::getSpotLightAttenuationLinear(int index) const {
    return spotLightLocation->attenuation.linear;
}

GLint Shader::getSpotLightAttenuationExp(int index) const {
    return spotLightLocation->attenuation.exp;
}

GLint Shader::getSpotLightDirection(int index) const {
    return spotLightLocation->direction;
}

GLint Shader::getSpotLightCutOff(int index) const {
    return spotLightLocation->cutOff;
}



