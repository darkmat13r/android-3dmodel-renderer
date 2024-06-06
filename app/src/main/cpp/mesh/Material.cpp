//
// Created by Dark Matter on 5/18/24.
//

#include "Material.h"
#include "string"
#include "AndroidOut.h"
#include "utils.h"

Shader *Material::getShader() const {
    return shader_;
}


void Material::loadShader() {
    shader_ = shaderLoader_->load(shaderPath);
}


Material::~Material() {
    aout << "Material::destroy" << std::endl;
}


void Material::unbindTexture() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Material::Material(ShaderLoader *shaderLoader) : shaderLoader_(shaderLoader) {
    diffuseColor = glm::vec4(0, 0, 0, 1);
    loadShader();
}

void Material::bindTexture() const {


    if (diffuseTexture) {
        glActiveTexture(COLOR_TEXTURE_UNIT);
        glBindTexture(GL_TEXTURE_2D, diffuseTexture->getTextureID());
        glUniform1i(shader_->getUseDiffTextureLocation(), GL_TRUE);
        glUniform1i(shader_->getDiffColorLocation(), COLOR_TEXTURE_UNIT_INDEX);
    }

    if (specularTexture) {
        glActiveTexture(SPECULAR_EXPONENT_UNIT);
        glBindTexture(GL_TEXTURE_2D, specularTexture->getTextureID());
        glUniform1i(shader_->getSpecularExponentLocation(), SPECULAR_EXPONENT_UNIT_INDEX);
    }

    //Push Color to fragment shader
    glUniform3fv(shader_->getAmbientColorLocation(), 1, (const GLfloat *) &ambientColor.x);

    glUniform3fv(shader_->getDiffColorLocation(), 1, (const GLfloat *) &diffuseColor.x);

    glUniform3fv(shader_->getSpecularColorLocation(), 1, (const GLfloat *) &specularColor.x);
}


