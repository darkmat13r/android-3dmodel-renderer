//
// Created by Dark Matter on 5/13/24.
//

#include "Scene.h"
#include "../Shader.h"
#include "../Model.h"
#include "../game/GameObject.h"

void Scene::Instantiate( Model gameObject) {
    this->gameObjects.emplace_back(gameObject);
}

void Scene::Render(const Shader &shader) {
    if(!gameObjects.empty()){
        for (const auto &gameObject: gameObjects) {
            // Use dynamic_cast to check if the gameObject is of type Model.
             const Model *model = dynamic_cast<const Model*>(&gameObject);
            // If the gameObject is a Model, then draw it.
            if (model != nullptr) {
                shader.drawModel(*model);
            }
        }
    }

}

Model * Scene::First() {
    return  &gameObjects[0];
}
