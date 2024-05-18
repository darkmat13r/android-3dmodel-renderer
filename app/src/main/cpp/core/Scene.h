//
// Created by Dark Matter on 5/13/24.
//

#ifndef LEARNOPENGL_SCENE_H
#define LEARNOPENGL_SCENE_H


#include "Component.h"
#include "../Model.h"

class Scene {
public:
    void addObject(Component *gameObject);

    void removeObject(Component *gameObject);

    void render(Mat4f* projectionMatrix);

private:
    std::vector<Component *> gameObjects;

    void update();
};


#endif //LEARNOPENGL_SCENE_H
