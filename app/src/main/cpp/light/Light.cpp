//
// Created by Dark Matter on 5/21/24.
//

#include "Light.h"

void Light::bind(Shader *shader) {
    if (shader->getLightColorLocation() != -1)
        glUniform3f(shader->getLightColorLocation(), color.r, color.g, color.b);

    if (shader->getAmbientIntensityLocation() != -1)
        glUniform1f(shader->getAmbientIntensityLocation(), ambientIntensity);
}

Light::Light() {

}

