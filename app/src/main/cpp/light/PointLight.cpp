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


