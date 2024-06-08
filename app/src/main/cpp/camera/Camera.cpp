//
// Created by Dark Matter on 5/13/24.
//

#include "Camera.h"
#include "glm/geometric.hpp"
#include "trigonometric.hpp"

void Camera::setPosition(float x, float y, float z) {
    transform->position.x = x;
    transform->position.y = y;
    transform->position.z = z;
}

void Camera::onUp() {
    // pos_ += (target_ * speed_);
    m_OnUpperEdge = true;
}

void Camera::onDown() {
    // pos_ -= (target_ * speed_);
    m_OnUpperEdge = true;
}

void Camera::onLeft() {
    /*  glm::vec3 left = target_.cross(up_);
      left.Normalize();
      left *= speed_;
      pos_ += left;*/
    m_OnLeftEdge = true;

}

void Camera::onRight() {
    /*  glm::vec3 right = up_.cross(target_);
      right.Normalize();
      right *= speed_;
      pos_ += right;*/
    m_OnRightEdge = true;
}

void Camera::panUp() {
    transform->position.y += speed_;
}

void Camera::panDown() {
    transform->position.y -= speed_;
}

void Camera::onMove() {

}

void Camera::onZoomIn() {

}

void Camera::onZoomOut() {

}

Mat4f Camera::matrix() {
    Mat4f cameraMat;
    cameraMat.lookAt(target_, transform->position, up_);
    return cameraMat;
}


void Camera::init() {
    glm::vec3 HTarget = glm::normalize(glm::vec3(target_.x, 0, target_.z));

    auto Angle = ToDegree(asinf(abs(HTarget.z)));

    if (HTarget.z >= 0.0f) {
        if (HTarget.x >= 0.0f) {
            m_AngleH = 360.0f - Angle;
        } else {
            m_AngleH = 180.0f + Angle;
        }
    } else {
        if (HTarget.x >= 0.0f) {
            m_AngleH = Angle;
        } else {
            m_AngleH = 180.0f - Angle;
        }
    }

    m_AngleV = -ToDegree(asinf(target_.y));
}

void Camera::onMove(float deltaX, float deltaY) {
    float radius = glm::length(transform->position - target_);

    angleX += deltaX;
    angleY += deltaY;

    // Constrain the vertical angle to avoid flipping
    angleY = glm::clamp(angleY, -0.0f, 90.0f);

    float radAngleX = glm::radians(angleX) * speed_;
    float radAngleY = glm::radians(angleY) * speed_;

    transform->position.x = target_.x + radius * cosf(radAngleX) * cosf(radAngleY);
    transform->position.y = target_.y + radius * cosf(radAngleX) * sinf(radAngleY);
    transform->position.z = target_.z + radius * sinf(radAngleX);


}

void Camera::moveForward(float distance) {
    transform->position.z += distance * speed_;
}
void Camera::moveLeft(float distance) {
    transform->position.x += distance * speed_;
}
void Camera::moveUp(float distance) {
    transform->position.y += distance * speed_;
}

void Camera::update() {
    /*glm::vec3 YAxis(0, 1, 0);

    glm::vec3 View(1, 0, 0);
    Rotate(m_AngleH, YAxis, View);
    View = glm::normalize(View);


    glm::vec3 U = glm::cross(YAxis, View);;
    U = glm::normalize(U);
    Rotate(m_AngleV, U, View);

    target_ = glm::normalize(View);

    up_ = glm::normalize(glm::cross(target_, U));*/




}


void Camera::onRender() {
    update();
    m_OnUpperEdge = false;
    m_OnUpperEdge = false;
    m_OnLeftEdge = false;
    m_OnRightEdge = false;

}

void Camera::rotate(float Angle, const glm::vec3 &V, glm::vec3 &target) {
    Quaternion RotationQ(Angle, V);
    Quaternion ConjugateQ = RotationQ.Conjugate();
    Quaternion W = RotationQ * target * ConjugateQ;

    target.x = W.x;
    target.y = W.y;
    target.z = W.z;
}

Camera::Camera(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up) {
    transform->setPosition(pos.x, pos.y, pos.z);
    target_ = target;
    up_ = up;

    init();
}

glm::vec3 Camera::getTarget() {
    return target_;
}

glm::vec3 &Camera::getPos() {
    return transform->position;
}

void Camera::setTarget(const glm::vec3& target) {
    target_ = target;
    angleY = glm::degrees(glm::dot(target, up_));
}




