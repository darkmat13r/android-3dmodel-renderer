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
    LightAttenuation attenuation;

    void calculateLocalPosition(const glm::vec3& worldTransform);

    glm::vec3  getLocalPosition();

private:
    glm::vec3  localPosition_;
};


#endif //LEARNOPENGL_POINTLIGHT_H
