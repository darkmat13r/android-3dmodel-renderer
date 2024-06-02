//
// Created by Dark Matter on 5/22/24.
//

#ifndef LEARNOPENGL_BEHAVIOUR_H
#define LEARNOPENGL_BEHAVIOUR_H


#include "Component.h"
#include "shader/Shader.h"

class Behaviour : public Component{
public:
    virtual void bind(Shader* shader, const glm::vec3 & cameraLocalPos);
};


#endif //LEARNOPENGL_BEHAVIOUR_H
