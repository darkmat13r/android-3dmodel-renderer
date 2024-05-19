//
// Created by Dark Matter on 5/13/24.
//

#include "Scene.h"
#include "../unused/ShaderBase.h"
#include "../Model.h"
#include "Utility.h"
#include "AndroidOut.h"
#include "mesh/MeshRenderer.h"

/*!
 * Half the height of the projection matrix. This gives you a renderable area of height 4 ranging
 * from -2 to 2
 */
static constexpr float kProjectionHalfHeight = 2.f;


/*!
 * The near plane distance for the projection matrix. Since this is an orthographic projection
 * matrix, it's convenient to have negative values for sorting (and avoiding z-fighting at 0).
 */
static constexpr float kProjectionNearPlane = 0.1;

/*!
 * The far plane distance for the projection matrix. Since this is an orthographic porjection
 * matrix, it's convenient to have the far plane equidistant from 0 as the near plane.
 */
static constexpr float kProjectionFarPlane = 5.f;

void Scene::addObject(const std::shared_ptr<Component>& gameObject) {
    this->components_.push_back(gameObject);
    gameObject->onAttach();
}

Camera *Scene::getMainCamera() const {
    return mainCamera_.get();
}

void Scene::render() {
    mainCamera_->OnRender();

    Mat4f View = mainCamera_->Matrix();

    for ( auto component : components_) {
        if (component->transform) {
            //component->transform->Rotate(0, rotation_, 0);
            Mat4f model = component->transform->Matrix();
            Mat4f finalProjectionMatrix = (*projectionMatrix_) * View * model;
            component->render(&finalProjectionMatrix);

        } else {
            aout << "Render::Component transform is gone " << component->transform << std::endl;
        }
    }
}

void Scene::update() {
    for (const auto &component: components_) {
        if (component && component->transform) {
            component->transform->Rotate(0, rotation_, 0);
            //  component->update();
        } else {
            aout << "Update::Component transform is gone " << component << std::endl;
        }
    }
}

void Scene::removeObject(Component *gameObject) {

}

void Scene::onDestroy() {

}

Scene::Scene(float width, float height) {
    setSize(width, height);
    glm::vec3 CameraPos(0.0f, 0.0f, -1.0f);
    glm::vec3 CameraTarget(0.0f, 0.0f, 1.0f);
    glm::vec3 CameraUp(0.0f, 1.0f, 0.0f);

    mainCamera_ = std::make_shared<Camera>( CameraPos, CameraTarget, CameraUp);
}

void Scene::setSize(float width, float height) {
    projectionMatrix_ = std::make_shared<Mat4f>();
    Utility::buildPerspectiveMat(
            projectionMatrix_.get(),
            kProjectionHalfHeight,
            float(width) / height,
            kProjectionNearPlane,
            kProjectionFarPlane);

}






