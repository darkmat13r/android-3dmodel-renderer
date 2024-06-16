//
// Created by Dark Matter on 5/23/24.
//

#include "DirectionalLight.h"
#include "Utility.h"

const glm::vec3 &DirectionalLight::GetLocalDirection() {
    return localDirection;
}

void DirectionalLight::calLocalDirection(const Transform& worldTransform) {
    //glm::mat3 world(glm::inverse(worldMat));
    localDirection = worldTransform.worldDirectionToLocal(direction);
}

void DirectionalLight::bind(Shader *shader, const glm::vec3 &cameraLocalPos) {
    Light::bind(shader, cameraLocalPos);
    glUniform1f(shader->lightTypeLocation, 1);

    if (shader->getLightDirectionLocation() != -1)
        glUniform3f(shader->getLightDirectionLocation(), localDirection.x, localDirection.y,
                    localDirection.z);

    if (shader->getDiffuseIntensityLocation() != -1)
        glUniform1f(shader->getDiffuseIntensityLocation(), diffuseIntensity);

    if (shader->getAmbientIntensityLocation() != -1)
        glUniform1f(shader->getAmbientIntensityLocation(), ambientIntensity);

    CHECK_GL_ERROR();
}

