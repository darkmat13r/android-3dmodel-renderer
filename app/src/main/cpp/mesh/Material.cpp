//
// Created by Dark Matter on 5/18/24.
//

#include "Material.h"

Shader *Material::getShader() const {
    return shader_.get();
}
