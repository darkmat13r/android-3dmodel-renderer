//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H


#include <__fwd/string.h>
#include <GLES3/gl3.h>
#include "detail/type_mat4x4.hpp"
#include "math/mat4f.h"

class Shader {
public:
    Shader(std::string& vertexShaderPath, std::string& fragmentShaderPath);
    void bind();
    void unbind();
    void setProjectionMatrix(const Mat4f* projectionMatrix);

private:
    GLuint program_ = 0;
    GLint projectionMatrixLocation_ = 0;
    GLint positionAttribute_ = 0;
    GLint uvAttribute_ = 0;
    std::string readFile(std::string &fileName) const;

    GLuint compileShader(std::string &shaderCode, GLenum shaderType);

};


#endif //LEARNOPENGL_SHADER_H
