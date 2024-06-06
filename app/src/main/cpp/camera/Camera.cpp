//
// Created by Dark Matter on 5/13/24.
//

#include "Camera.h"
#include "glm/geometric.hpp"

void Camera::SetPosition(float x, float y, float z) {
    transform->position.x = x;
    transform->position.y = y;
    transform->position.z = z;
}

void Camera::OnUp() {
    // pos_ += (target_ * speed_);
    m_OnUpperEdge = true;
}

void Camera::OnDown() {
    // pos_ -= (target_ * speed_);
    m_OnUpperEdge = true;
}

void Camera::OnLeft() {
    /*  glm::vec3 left = target_.cross(up_);
      left.Normalize();
      left *= speed_;
      pos_ += left;*/
    m_OnLeftEdge = true;

}

void Camera::OnRight() {
    /*  glm::vec3 right = up_.cross(target_);
      right.Normalize();
      right *= speed_;
      pos_ += right;*/
    m_OnRightEdge = true;
}

void Camera::PanUp() {
    transform->position.y += speed_;
}

void Camera::PanDown() {
    transform->position.y -= speed_;
}

void Camera::OnMove() {

}

void Camera::OnZoomIn() {

}

void Camera::OnZoomOut() {

}

Mat4f Camera::Matrix() {
    Mat4f cameraMat;
    cameraMat.InitCamera(target_, transform->position, up_);
    return cameraMat;
}


void Camera::Init() {
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

void Camera::OnMove(int deltaX, int deltaY) {
    m_AngleH += (float) deltaX / 20;
    m_AngleV += (float) deltaY / 20;
}

void Camera::MoveForward(float distance) {
    transform->position.z += distance * speed_;
}
void Camera::MoveLeft(float distance) {
    transform->position.x += distance * speed_;
}
void Camera::MoveUp(float distance) {
    transform->position.y += distance * speed_;
}

void Camera::Update() {
    glm::vec3 YAxis(0, 1, 0);

    glm::vec3 View(1, 0, 0);
    Rotate(m_AngleH, YAxis, View);
    View = glm::normalize(View);


    glm::vec3 U = glm::cross(YAxis, View);;
    U = glm::normalize(U);
    Rotate(m_AngleV, U, View);

    target_ = glm::normalize(View);

    up_ = glm::normalize(glm::cross(target_, U));
}


void Camera::OnRender() {
    Update();
    m_OnUpperEdge = false;
    m_OnUpperEdge = false;
    m_OnLeftEdge = false;
    m_OnRightEdge = false;

}

void Camera::Rotate(float Angle, const glm::vec3 &V, glm::vec3 &target) {
    Quaternion RotationQ(Angle, V);
    Quaternion ConjugateQ = RotationQ.Conjugate();
    Quaternion W = RotationQ * target * ConjugateQ;

    target.x = W.x;
    target.y = W.y;
    target.z = W.z;
}

Camera::Camera(const glm::vec3 &pos, const glm::vec3 &targe, const glm::vec3 &up) {
    transform->setPosition(pos.x, pos.y, pos.z);
    target_ = targe;
    up_ = up;

    Init();
}




