//
// Created by Dark Matter on 5/18/24.
//

#include "Shader.h"
#include "AndroidOut.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Vertex shader, you'd typically load this from assets
static const char *vertexShaderSource = R"vertex(#version 300 es
in vec3 inPosition;
in vec2 inUV;

out vec2 fragUV;

uniform mat4 uProjection;

void main() {
    fragUV = inUV;
    gl_Position = uProjection * vec4(inPosition, 1.0);
}
)vertex";

// Fragment shader, you'd typically load this from assets
static const char *fragmentShaderSource = R"fragment(#version 300 es
precision mediump float;

in vec2 fragUV;

uniform sampler2D uTexture;
uniform vec4 uDiffColor;
uniform bool uUseTexture;

out vec4 outColor;

void main() {
    if(uUseTexture){
        vec4 textureColor  = texture(uTexture, fragUV);
        outColor =  textureColor;
    }else{
        outColor =  uDiffColor;
    }

}
)fragment";


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
        diffuseColorLocation_ = glGetUniformLocation(program_, "uDiffColor");
        useDiffText_ = glGetUniformLocation(program_, "uUseTexture");
        positionAttribute_ = glGetAttribLocation(program_, "inPosition");
        uvAttribute_ = glGetAttribLocation(program_, "inUV");
        if (projectionMatrixLocation_ == -1
            || positionAttribute_ == -1
            || useDiffText_ == -1
            || diffuseColorLocation_ == -1
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

void Shader::unbind() const{
    glUseProgram(0);
}

void Shader::setProjectionMatrix(const Mat4f *projectionMatrix) const{
    glUniformMatrix4fv(projectionMatrixLocation_, 1, GL_TRUE, &projectionMatrix->m[0][0]);
}

GLint Shader::getDiffColorLocation() const {
    return diffuseColorLocation_;
}

GLint Shader::getUseDiffTextureLocation() const {
    return useDiffText_;
}

