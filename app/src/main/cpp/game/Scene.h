//
// Created by Dark Matter on 5/13/24.
//

#ifndef LEARNOPENGL_SCENE_H
#define LEARNOPENGL_SCENE_H


#include "GameObject.h"
#include "../Model.h"
#include "../mesh/Shader.h"

class Scene {
public:
    void Instantiate(const std::shared_ptr<Model>& gameObject);
    void Render( Shader &shader);
    Model * First();
    Model *Last();

private:
    std::vector<std::shared_ptr<Model>> gameObjects;
};


#endif //LEARNOPENGL_SCENE_H
