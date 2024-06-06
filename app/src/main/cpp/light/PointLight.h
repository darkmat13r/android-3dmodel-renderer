//
// Created by Dark Matter on 6/4/24.
//

#ifndef LEARNOPENGL_POINTLIGHT_H
#define LEARNOPENGL_POINTLIGHT_H


#include "Light.h"

struct LightAttenuation{
    float constant = 1.0;
    float linear = 0.0;
    float exp = 0.0;
};

class PointLight : public Light{

public :
    int index = 0;
    LightAttenuation attenuation;

    void calculateLocalPosition(const Transform& worldTransform);

    glm::vec3  getLocalPosition();

    void bind(Shader *shader, const glm::vec3 &cameraLocalPos) override;

private:
    glm::vec3  localPosition_;
};


#endif //LEARNOPENGL_POINTLIGHT_H
