//
// Created by Dark Matter on 5/13/24.
//

#include "Camera.h"
#include "glm/geometric.hpp"

void Camera::SetPosition(float x, float y, float z) {
    pos_.x = x;
    pos_.y = y;
    pos_.z = z;
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
    pos_.y += speed_;
}

void Camera::PanDown() {
    pos_.y -= speed_;
}

void Camera::OnMove() {

}

void Camera::OnZoomIn() {

}

void Camera::OnZoomOut() {

}

Mat4f Camera::Matrix() {
    Mat4f cameraMat;
    cameraMat.InitCamera(target_, pos_, up_);
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

void Camera::OnMove(int DeltaX, int deltaY) {
    m_AngleH += (float) DeltaX / 20;
    m_AngleV += (float) deltaY / 20;


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

Camera::Camera(int WindowWidth, int WindowHeight, const glm::vec3 &Pos, const glm::vec3 &Target,
               const glm::vec3 &Up) {

    m_windowWidth = WindowWidth;
    m_windowHeight = WindowHeight;
    pos_ = Pos;
    target_ = Target;
    up_ = Up;

    Init();
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



