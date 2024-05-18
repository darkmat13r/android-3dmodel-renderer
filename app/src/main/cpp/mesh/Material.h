//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_MATERIAL_H
#define LEARNOPENGL_MATERIAL_H


#include "mesh/shader/Shader.h"

class Material {
public:
    Shader* getShader() const;
private :
    std::shared_ptr<Shader> shader_;
};


#endif //LEARNOPENGL_MATERIAL_H
