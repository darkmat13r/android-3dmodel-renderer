//
// Created by Dark Matter on 5/13/24.
//

#ifndef LEARNOPENGL_SCENE_H
#define LEARNOPENGL_SCENE_H


#include "Component.h"
#include "../Model.h"
#include "camera/Camera.h"
#include "mesh/MeshRenderer.h"


class Scene {
public:
    Scene(float width, float height);

    void setSize(float width, float height);

    void addObject(const std::shared_ptr<Component> &gameObject);

    void removeObject(Component *gameObject);

    void render();

    void update();

    void onDestroy();

    Camera *getMainCamera() const;

private:
    std::vector<std::shared_ptr<Component>> components_;
    std::shared_ptr<Camera> mainCamera_;
    std::shared_ptr<Mat4f> projectionMatrix_;
    float rotation_ = 0.2;
    float deltaY = 0.2;

};


#endif //LEARNOPENGL_SCENE_H
