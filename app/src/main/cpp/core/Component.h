//
// Created by Dark Matter on 5/13/24.
//

#ifndef LEARNOPENGL_COMPONENT_H
#define LEARNOPENGL_COMPONENT_H

#include "../transform/Transform.h"

class Component {

public:
    Component() ;
    ~ Component();
    std::shared_ptr<Transform> transform;
    virtual void onAttach();
    virtual void onCreate();
    virtual void render(glm::mat4* f);
    virtual void update();
    virtual void onDestroy();

};

#endif //LEARNOPENGL_COMPONENT_H
