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

    glm::vec3 diffuseColor = {1.0, 1.0, 1.0};
    glm::vec3 ambientColor = {1.0, 1.0, 1.0};

    Material(std::shared_ptr<TextureAsset> textureAsset);
    Material(glm::vec4 diffuseColor);

    Material();

    ~Material();

    Shader *getShader() const;

    void bindTexture() const;

    void unbindTexture() const;


private :
    std::shared_ptr<Shader> shader_;
    std::shared_ptr<TextureAsset> diffuseTexture_;
    void loadShader();
};


#endif //LEARNOPENGL_MATERIAL_H
