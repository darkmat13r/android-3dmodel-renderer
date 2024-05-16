//
// Created by Dark Matter on 5/13/24.
//

#ifndef LEARNOPENGL_SCENE_H
#define LEARNOPENGL_SCENE_H


#include "GameObject.h"
#include "../Model.h"
#include "../Shader.h"

class Scene {
public:
    void Instantiate(Model gameObject);

    void Render(const Shader &shader);
    Model * First();

private:
    std::vector<Model> gameObjects;
};


#endif //LEARNOPENGL_SCENE_H
