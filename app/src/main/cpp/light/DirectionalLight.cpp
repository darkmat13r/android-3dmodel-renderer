//
// Created by Dark Matter on 5/23/24.
//

#include "DirectionalLight.h"

const glm::vec3 &DirectionalLight::GetLocalDirection() {
    return localDirection;
}

void DirectionalLight::CalLocalDirection(glm::mat4 worldMat) {
    glm::mat3 world(glm::inverse(worldMat));
    localDirection = -glm::normalize(direction * world);
}

void DirectionalLight::bind(Shader *shader) {
    Light::bind(shader);
    glUniform1i(shader->lightTypeLocation, 1);

    if (shader->lightDirectionLocation != -1)
        glUniform3f(shader->lightDirectionLocation, localDirection.x, localDirection.y,
                    localDirection.z);

    if (shader->diffuseIntensityLocation != -1)
        glUniform1f(shader->diffuseIntensityLocation, intensity);
}

