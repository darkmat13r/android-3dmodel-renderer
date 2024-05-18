//
// Created by Dark Matter on 5/13/24.
//

#include "Scene.h"
#include "../Shader.h"
#include "../Model.h"
#include "../game/GameObject.h"

void Scene::Instantiate(const std::shared_ptr<Model> &gameObject) {
    this->gameObjects.emplace_back(gameObject);
}


void Scene::Render(Shader &shader) {
    if (!gameObjects.empty()) {
        for (const auto &gameObject: gameObjects) {
            // Use dynamic_cast to check if the gameObject is of type Model.
             Model *model = gameObject.get();
            // If the gameObject is a Model, then draw it.
            if (model != nullptr) {
                shader.drawModel(model);
            }
        }
    }

}

Model *Scene::First() {
    return gameObjects[0].get();
}


Model *Scene::Last() {
    if (gameObjects.size() == 0) return nullptr;
    return gameObjects[gameObjects.size() - 1].get();
}



