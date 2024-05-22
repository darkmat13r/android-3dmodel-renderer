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
    virtual void render(Mat4f* f);
    virtual void update();
    virtual void onDestroy();
    virtual void onAttach();
    virtual void onCreate();

};

#endif //LEARNOPENGL_COMPONENT_H
