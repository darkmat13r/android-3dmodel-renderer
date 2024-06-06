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

    void calLocalDirection(Mat4f worldMat);
    void bind(Shader *shader, const glm::vec3 & cameraLocalPos) override;

    const glm::vec3 &GetLocalDirection();
};


#endif //LEARNOPENGL_DIRECTIONALLIGHT_H
