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
    GLint diffuseIntensityLocation = 0;
    GLint lightDirectionLocation = 0;
    GLint lightTypeLocation = 0;
    GLint normalAttribute = 0;


    Shader(std::string &vertexShaderPath, std::string &fragmentShaderPath);

    void bind() const;

    void unbind() const;

    void setProjectionMatrix(const Mat4f *projectionMatrix) const;

    GLint getPositionAttrib() const;

    GLint getDiffColorLocation() const;

    GLint getUseDiffTextureLocation() const;

    GLint getUvAttrib() const;

    GLint getAmbientColorLocation() const;

    GLint getAmbientIntensityLocation() const;

    GLint getLightColorLocation() const;

    GLint getSpecularExponentLocation() const;

    GLint getSpecularColorLocation() const;

    GLint getCameraLocalPosLocation() const;

private:
    GLuint program_ = 0;
    GLint projectionMatrixLocation_ = 0;
    GLint positionAttribute_ = 0;
    GLint uvAttribute_ = 0;
    GLint diffuseColorLocation_ = 0;
    GLint useDiffText_ = 0;
    GLint ambientColorLocation_ = 0;
    GLint lightColorLocation_ = 0;
    GLint lightAmbientIntensityLocation_ = 0;
    GLint samplerSpecularExponentLocation = 0;
    GLint specularColorLocation = 0;
    GLint cameraLocalPosLocation = 0;

    std::string readFile(std::string &fileName) const;

    static GLuint compileShader(const char *shaderCode, GLenum shaderType);

};


#endif //LEARNOPENGL_SHADER_H
