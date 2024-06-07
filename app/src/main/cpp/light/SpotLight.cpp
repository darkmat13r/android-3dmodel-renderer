//
// Created by Dark Matter on 6/7/24.
//

#include "SpotLight.h"

void SpotLight::calculateDirectionAndPosition(const Transform &transform) {
    calculateLocalPosition(transform);
    localDirection = transform.worldDirectionToLocal(direction);
}

glm::vec3 SpotLight::getLocalDirection() {
    return localDirection;
}

void SpotLight::bind(Shader *shader, const glm::vec3 &cameraLocalPos) {
    Light::bind(shader, cameraLocalPos);

    glUniform3f(shader->getSpotLightColor(index), color.r, color.g,  color.b);
    glUniform1f(shader->getSpotLightAmbientIntensity(index), ambientIntensity );
    glUniform1f(shader->getSpotLightDiffuseIntensity(index), diffuseIntensity );
    glUniform3f(shader->getSpotLightLocalPosition(index), localPosition_.x, localPosition_.y, localPosition_.z );
    glUniform1f(shader->getSpotLightAttenuationConstant(index), attenuation.constant);
    glUniform1f(shader->getSpotLightAttenuationLinear(index), attenuation.linear);
    glUniform1f(shader->getSpotLightAttenuationExp(index), attenuation.exp);

    glm::vec3 localDirectionNorm = glm::normalize(localDirection);
    glUniform3f(shader->getSpotLightDirection(index), localDirectionNorm.x, localDirectionNorm.y, localDirectionNorm.z);
    glUniform1f(shader->getSpotLightDirection(index), cutOff);
}

