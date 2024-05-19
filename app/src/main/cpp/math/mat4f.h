//
// Created by Dark Matter on 5/16/24.
//

#ifndef LEARNOPENGL_MAT4F_H
#define LEARNOPENGL_MAT4F_H


#include <cmath>
#include <memory>
#include "glm/detail/type_vec3.hpp"
#include "glm/vec3.hpp"

struct Mat4f {
    float m[4][4];

    // Constructors
    Mat4f();
    Mat4f(float a00, float a01, float a02, float a03,
          float a10, float a11, float a12, float a13,
          float a20, float a21, float a22, float a23,
          float a30, float a31, float a32, float a33);

    // Member functions
    void InitScaleMatrix(float scaleX, float scaleY, float scaleZ);
    void InitRotationX(float x);
    void InitRotationY(float y);
    void InitRotationZ(float z);
    void InitRotationMatrix(float rotationX, float rotationY, float rotationZ);
    void InitTranslation(float x, float y, float z);
    void InitCameraTransform(glm::vec3 Target, glm::vec3 Up);
    void InitCamera(glm::vec3 target, glm::vec3 pos, glm::vec3 up);
    void InitIdentity();

    // Static method to create an identity matrix and return a unique_ptr
    static std::unique_ptr<Mat4f> Identity();

    // Overloaded operators
    Mat4f operator*(const Mat4f &other) const;
};


#endif //LEARNOPENGL_MAT4F_H
