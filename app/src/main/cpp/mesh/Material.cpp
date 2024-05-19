//
// Created by Dark Matter on 5/18/24.
//

#include "Material.h"
#include "string"
#include "AndroidOut.h"

Shader *Material::getShader() const {
    return shader_.get();
}

Material::Material() {
    std::string vertexShaderPath = "shaders/base_frag.vert";
    std::string fragmentShaderPath = "shaders/base_frag.frag";

    shader_ = std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
}

Material::~Material() {
    aout << "Material::destroy" << std::endl;
}
