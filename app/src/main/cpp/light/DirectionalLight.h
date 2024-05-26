//
// Created by Dark Matter on 5/23/24.
//

#ifndef LEARNOPENGL_DIRECTIONALLIGHT_H
#define LEARNOPENGL_DIRECTIONALLIGHT_H


#include "Light.h"

class DirectionalLight : public Light {
private:
    glm::vec3 localDirection = {0, 0, 0};
public :
    glm::vec3 direction = {0, 0, 0};
    float intensity = 1.0;

    void CalLocalDirection(Mat4f worldMat);
    void bind(Shader *shader) override;

    const glm::vec3 &GetLocalDirection();
};


#endif //LEARNOPENGL_DIRECTIONALLIGHT_H
