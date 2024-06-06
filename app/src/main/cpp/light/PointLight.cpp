//
// Created by Dark Matter on 6/4/24.
//

#include "PointLight.h"

void PointLight::calculateLocalPosition(const glm::vec3 &worldTransform) {
   localPosition_ = transform->worldToLocal(worldTransform);
}

glm::vec3 PointLight::getLocalPosition() {
    return localPosition_;
}

void PointLight::bind(Shader *shader, const glm::vec3 &cameraLocalPos) {
    Light::bind(shader, cameraLocalPos);

    glUniform3f(shader->getPointLightColor(index), color.r, color.g,  color.b);
    glUniform1f(shader->getPointLightAmbientIntensity(index), ambientIntensity );
    glUniform1f(shader->getPointLightDiffuseIntensity(index), diffuseIntensity );
    glUniform3f(shader->getPointLightLocalPosition(index), localPosition_.x, localPosition_.y, localPosition_.z );
    glUniform1f(shader->getPointLightAttenuationConstant(index), attenuation.constant);
    glUniform1f(shader->getPointLightAttenuationLinear(index), attenuation.linear);
    glUniform1f(shader->getPointLightAttenuationExp(index), attenuation.exp);
}


