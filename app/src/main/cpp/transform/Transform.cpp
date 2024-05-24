//
// Created by Dark Matter on 5/8/24.
//

#include "Transform.h"
#include "AndroidOut.h"
#include "glm.hpp"

void Transform::setScale(float scaleX, float scaleY, float scaleZ) {
    this->scale_.x = scaleX;
    this->scale_.y = scaleY;
    this->scale_.z = scaleZ;
}

void Transform::setPosition(float x, float y, float z) {
    this->position_.x = x;
    this->position_.y = y;
    this->position_.z = z;
}

void Transform::setRotation(float x, float y, float z) {
    this->rotation_.x = x;
    this->rotation_.y = y;
    this->rotation_.z = z;
}

void Transform::rotate(float x, float y, float z) {
    this->rotation_.x += x;
    this->rotation_.y += y;
    this->rotation_.z += z;
}

glm::mat4 Transform::matrix() {
    auto rotMat = glm::mat4(1.0);

    InitRotationMatrix(rotMat, rotation_.x, rotation_.y, rotation_.z);

    auto transMat = glm::mat4(1.0);;
    InitTranslation(transMat, position_.x, position_.y, position_.z);

    auto scaleMat = glm::mat4(1.0);;
   // InitScaleMatrix(scaleMat, scale_.x, scale_.y, scale_.z);

    return transMat * rotMat * scaleMat;
}

Transform::Transform() :
        position_(0, 0, 0),
        rotation_(0, 0, 0, 0),
        scale_(1, 1, 1) {
}
