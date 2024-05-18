//
// Created by Dark Matter on 5/13/24.
//

#include "Scene.h"
#include "../unused/ShaderBase.h"
#include "../Model.h"
#include "../game/GameObject.h"

void Scene::addObject( GameObject* gameObject) {
    this->gameObjects.push_back(gameObject);
}

void Scene::render(Mat4f* projectionMatrix) {
    for (const auto &item: gameObjects){
        item->render(projectionMatrix);
    }
}

void Scene::update(){
    for (const auto &item: gameObjects){
        item->update();
    }
}

void Scene::removeObject(GameObject* gameObject) {

}






