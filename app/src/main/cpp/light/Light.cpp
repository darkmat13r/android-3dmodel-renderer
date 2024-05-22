//
// Created by Dark Matter on 5/21/24.
//

#include "Light.h"

void Light::bind(Shader *shader) {
    glUniform4f(shader->getLightColorLocation(), color.r, color.g, color.b, 1.0);
    glUniform1f(shader->getAmbientIntensityLocation(), ambientIntensity);
}

Light::Light() {

}

