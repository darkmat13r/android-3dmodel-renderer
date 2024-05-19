//
// Created by Dark Matter on 5/18/24.
//

#include "Material.h"
#include "string"
#include "AndroidOut.h"

Shader *Material::getShader() const {
    return shader_.get();
}

Material::Material(std::shared_ptr<TextureAsset> textureAsset) : diffuseTexture_(
        std::move(textureAsset)) {
    std::string vertexShaderPath = "shaders/base_frag.vert";
    std::string fragmentShaderPath = "shaders/base_frag.frag";

    shader_ = std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
}

Material::~Material() {
    aout << "Material::destroy" << std::endl;
}

void Material::bindTexture() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTexture_->getTextureID());
}
