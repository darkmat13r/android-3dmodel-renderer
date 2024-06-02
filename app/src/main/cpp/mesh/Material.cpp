//
// Created by Dark Matter on 5/18/24.
//

#include "Material.h"
#include "string"
#include "AndroidOut.h"
#include "utils.h"

Shader *Material::getShader() const {
    return shader_.get();
}


void Material::loadShader() {
    std::string vertexShaderPath = "shaders/base_frag.vert";
    std::string fragmentShaderPath = "shaders/base_frag.frag";

    shader_ = std::__ndk1::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
}


Material::Material(glm::vec3 diffuseColor) : diffuseColor(diffuseColor) {
    loadShader();
}


Material::~Material() {
    aout << "Material::destroy" << std::endl;
}


void Material::unbindTexture() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Material::Material() {
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


