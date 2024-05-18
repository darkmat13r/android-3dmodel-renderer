//
// Created by Dark Matter on 5/13/24.
//

#ifndef LEARNOPENGL_SCENE_H
#define LEARNOPENGL_SCENE_H


#include "GameObject.h"
#include "../Model.h"
#include "../unused/ShaderBase.h"

class Scene {
public:
    void addObject(GameObject *gameObject);

    void removeObject(GameObject *gameObject);

    void render(Mat4f* projectionMatrix);

private:
    std::vector<GameObject *> gameObjects;

    void update();
};


#endif //LEARNOPENGL_SCENE_H
