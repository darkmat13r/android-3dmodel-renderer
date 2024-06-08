//
// Created by Dark Matter on 5/8/24.
//

#include "Transform.h"
#include "AndroidOut.h"
#include "geometric.hpp"

void Transform::setScale(float scaleX, float scaleY, float scaleZ) {
    this->scale_.x = scaleX;
    this->scale_.y = scaleY;
    this->scale_.z = scaleZ;
}

void Transform::setPosition(float x, float y, float z) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
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

Mat4f Transform::getReversedTranslation() const {
    Mat4f reversedTranslation;
    reversedTranslation.initTranslation(-position.x, -position.y, -position.z);
    return reversedTranslation;
}

glm::vec3 Transform::worldToLocal(glm::vec3 worldPosition) const{
    Mat4f cameraToLocalTranslation = getReversedTranslation();
    Mat4f cameraToLocalRotation = getReversedRotation();
    Mat4f cameraToLocalTransformation = cameraToLocalRotation * cameraToLocalTranslation;
    glm::vec4 cameraWorldPos = glm::vec4 (worldPosition, 1.0);
    glm::vec4 cameraLocalPos = cameraToLocalTransformation * cameraWorldPos;
    return cameraWorldPos;
}

Mat4f Transform::getReversedRotation() const{
    Mat4f reversedTranslation;
    reversedTranslation.initRotationMatrix(-rotation_.x, -rotation_.y, -rotation_.z);
    return reversedTranslation;
}

Mat4f Transform::matrix() const {
    Mat4f rotMat;

    rotMat.initRotationMatrix(rotation_.x, rotation_.y, rotation_.z);

    Mat4f transMat;
    transMat.initTranslation(position.x, position.y, position.z);

    Mat4f scaleMat;
    scaleMat.initScaleMatrix(scale_.x, scale_.y, scale_.z);

    return transMat * rotMat * scaleMat;
}

Transform::Transform() :
        position(0, 0, 0),
        rotation_(0, 0, 0, 0),
        scale_(1, 1, 1) {
}

glm::vec3 Transform::getPosition() {
    return position;
}

void Transform::setYPosition(float y) {
    this->position.y = y;
}

float Transform::getPositionY() {
    return position.y;
}

glm::vec3 Transform::worldDirectionToLocal(glm::vec3 direction) const {
    Mat3f world3Mat(matrix());

    //TODO non-uniform scaling is not supported yet. Calculate the inverse of the matrix instead of using transpose
    return -glm::normalize(world3Mat.Transpose() *
                                     direction);
}
