//
// Created by Dark Matter on 6/7/24.
//

#ifndef LEARNOPENGL_SPOTLIGHT_H
#define LEARNOPENGL_SPOTLIGHT_H


#include "PointLight.h"

class SpotLight : public PointLight {
public:
    glm::vec3 direction;
    float cutOff = 0.0;

    void calculateDirectionAndPosition(const Transform &transform);

    glm::vec3 getLocalDirection();

    void bind(Shader *shader, const glm::vec3 &cameraLocalPos) override;

private:
    glm::vec3 localDirection;
};


#endif //LEARNOPENGL_SPOTLIGHT_H
