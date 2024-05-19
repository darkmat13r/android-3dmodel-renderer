//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_MATERIAL_H
#define LEARNOPENGL_MATERIAL_H


#include "mesh/shader/Shader.h"
#include "TextureAsset.h"

class Material {
public:
    explicit Material(std::shared_ptr<TextureAsset> textureAsset);
    ~Material();
    Shader* getShader() const;
    void bindTexture() const;
private :
    std::shared_ptr<Shader> shader_;
    std::shared_ptr<TextureAsset> spTexture_;
    GLuint diffuseTextureId_;
};


#endif //LEARNOPENGL_MATERIAL_H
