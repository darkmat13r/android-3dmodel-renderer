//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H


#include <__fwd/string.h>

class Shader {
public:
    Shader(std::string& fragmentShader, std::string& vertexShader);
    void bind();
    void unbind();
    void setProjectionMatrix();

private:

};


#endif //LEARNOPENGL_SHADER_H
