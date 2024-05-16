//
// Created by Dark Matter on 5/13/24.
//

#include "Camera.h"

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
    /*  Vector3 left = target_.cross(up_);
      left.Normalize();
      left *= speed_;
      pos_ += left;*/
    m_OnLeftEdge = true;

}

void Camera::OnRight() {
    /*  Vector3 right = up_.cross(target_);
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
    Vector3 HTarget = Vector3(target_.x, 0, target_.z);
    HTarget.Normalize();

    float Angle = ToRadian(asinf(abs(HTarget.z)));

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

    m_AngleV = -ToRadian(asinf(target_.y));
}

void Camera::OnMove(int DeltaX, int deltaY) {
    m_AngleH += (float) DeltaX / 20;
    m_AngleV += (float) deltaY / 20;


}

void Camera::Update() {
    Vector3 YAxis(0, 0, 0);

    Vector3 View(1, 0, 0);
    View.Rotate(m_AngleH, YAxis);
    View.Normalize();


    Vector3 U = YAxis.cross(View);
    U.Normalize();
    View.Rotate(m_AngleV, U);
    target_ = View;
    target_.Normalize();

    up_ = target_.cross(U);
    up_.Normalize();
}

Camera::Camera(int WindowWidth, int WindowHeight, const Vector3 &Pos, const Vector3 &Target,
               const Vector3 &Up) {

    m_windowWidth = WindowWidth;
    m_windowHeight = WindowHeight;
    pos_          = Vector3(0.0f, 1.0f, 0.0f);
    target_       = Vector3(0.0f, 0.0f, 1.0f);
    up_           = Vector3(0.0f, 1.0f, 0.0f);
    //Init();
}

void Camera::OnRender() {
    //Update();
    m_OnUpperEdge = false;
    m_OnUpperEdge = false;
    m_OnLeftEdge = false;
    m_OnRightEdge = false;

}



