//
// Created by Dark Matter on 5/13/24.
//

#ifndef LEARNOPENGL_SCENE_H
#define LEARNOPENGL_SCENE_H


#include "Component.h"
#include "../Model.h"
#include "camera/Camera.h"


class Scene {
public:
    Scene(float width, float height);

    void addObject(Component* gameObject);

    void removeObject(Component *gameObject);

    void render();

    void update();

    void onDestroy();

    Camera *getMainCamera() const;

private:
    std::vector<Component*> components_;
    std::shared_ptr<Camera> mainCamera_;
    std::unique_ptr<Mat4f> projectionMatrix_;
    float rotation_;

};


#endif //LEARNOPENGL_SCENE_H
