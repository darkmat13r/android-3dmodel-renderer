//
// Created by Dark Matter on 6/6/24.
//

#ifndef LEARNOPENGL_SHADERLOADER_H
#define LEARNOPENGL_SHADERLOADER_H

#include "Shader.h"
#include <unordered_map>
#include <memory>
#include <string>

class ShaderLoader {
private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_;

public:
    ShaderLoader();
    void setNumOfLights(int count) const;
    Shader *load(const char *name);
};


#endif //LEARNOPENGL_SHADERLOADER_H
