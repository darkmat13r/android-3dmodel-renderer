//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_MATERIAL_H
#define LEARNOPENGL_MATERIAL_H


#include "shader/Shader.h"
#include "TextureAsset.h"

class Material {
public:
    std::string materialName;
    std::shared_ptr<TextureAsset> diffuseTexture;
    std::shared_ptr<TextureAsset> specularTexture;

    glm::vec3 diffuseColor = {1.0, 1.0, 1.0};
    glm::vec3 specularColor = {1.0, 1.0, 1.0};
    glm::vec3 ambientColor = {0.0, 0.0, 0.0};

    Material();

    explicit Material(glm::vec3 diffuseColor);

    ~Material();

    Shader *getShader() const;

    void bindTexture() const;

    void unbindTexture() const;


private :
    std::shared_ptr<Shader> shader_;

    void loadShader();
};


#endif //LEARNOPENGL_MATERIAL_H
