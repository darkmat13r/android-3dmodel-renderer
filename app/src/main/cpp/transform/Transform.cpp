//
// Created by Dark Matter on 5/8/24.
//

#include "Transform.h"

void Transform::SetScale(float scaleX, float scaleY, float scaleZ) {
    this->scale_.x = scaleX;
    this->scale_.y = scaleY;
    this->scale_.z = scaleZ;
}

void Transform::SetPosition(float x, float y, float z) {
    this->position_.x = x;
    this->position_.y = y;
    this->position_.z = z;
}

void Transform::SetRotation(float x, float y, float z) {
    this->rotation_.x = x;
    this->rotation_.y = y;
    this->rotation_.z = z;
}

void Transform::Rotate(float x, float y, float z) {
    this->rotation_.x += x;
    this->rotation_.y += y;
    this->rotation_.z += z;
}

Mat4f Transform::Matrix() {
    Mat4f rotMat;
    rotMat.InitRotationMatrix(rotation_.x, rotation_.y, rotation_.z);

    Mat4f transMat;
    transMat.InitTranslation(position_.x, position_.y, position_.z);

    Mat4f scaleMat;
    scaleMat.InitScaleMatrix(scale_.x, scale_.y, scale_.z);

    return transMat * rotMat *  scaleMat;
}
