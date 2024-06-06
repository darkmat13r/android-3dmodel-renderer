//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_MATERIAL_H
#define LEARNOPENGL_MATERIAL_H


#include "shader/Shader.h"
#include "TextureAsset.h"
#include "string"
#include "shader/ShaderLoader.h"

class Material {
public:
    std::string materialName;
    std::shared_ptr<TextureAsset> diffuseTexture;
    std::shared_ptr<TextureAsset> specularTexture;

    glm::vec3 diffuseColor = {0.0, 0.0, 0.0};
    glm::vec3 specularColor = {0.0, 0.0, 0.0};
    glm::vec3 ambientColor = {0.0, 0.0, 0.0};

    Material(ShaderLoader* shaderLoader);

    ~Material();

    Shader *getShader() const;

    void bindTexture() const;

    void unbindTexture() const;


private :
    Shader* shader_;
    std::shared_ptr<ShaderLoader> shaderLoader_;
    const char* shaderPath = "default";

    void loadShader();
};


#endif //LEARNOPENGL_MATERIAL_H
