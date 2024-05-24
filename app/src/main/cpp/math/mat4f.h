//
// Created by Dark Matter on 5/16/24.
//

#ifndef LEARNOPENGL_MAT4F_H
#define LEARNOPENGL_MAT4F_H


#include <cmath>
#include <memory>
#include "glm/detail/type_vec3.hpp"
#include "glm/vec3.hpp"
#include "geometric.hpp"
#include "glm.hpp"
#include "math.h"
#include "AndroidOut.h"

// Initialize identity matrix
inline void initIdentity(glm::mat4 *m) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            (*m)[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

// Initialize scale matrix
inline void InitScaleMatrix(glm::mat4 &m, float scaleX, float scaleY, float scaleZ) {
    m[0][0] = scaleX;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = scaleY;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = scaleZ;
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

// Initialize rotation matrix around X axis
inline void InitRotationX(glm::mat4 &m, float x) {
    m[1][1] = cosf(x);
    m[1][2] = sinf(x);
    m[2][1] = -sinf(x);
    m[2][2] = cosf(x);
}

// Initialize rotation matrix around Y axis
inline void InitRotationY(glm::mat4 &m, float y) {
    m[0][0] = cosf(y);
    m[0][2] = -sinf(y);
    m[2][0] = sinf(y);
    m[2][2] = cosf(y);
}

// Initialize rotation matrix around Z axis
inline void InitRotationZ(glm::mat4 &m, float z) {
    m[0][0] = cosf(z);
    m[0][1] = sinf(z);
    m[1][0] = -sinf(z);
    m[1][1] = cosf(z);
}

// Initialize rotation matrix for combined rotations
inline void InitRotationMatrix(glm::mat4 &m, float rotationX, float rotationY, float rotationZ) {
    glm::mat4 rx = glm::mat4 (1.0);
    glm::mat4 ry = glm::mat4 (1.0);
    glm::mat4 rz = glm::mat4 (1.0);


    float x = ToRadian(rotationX);
    float y = ToRadian(rotationY);
    float z = ToRadian(rotationZ);

    InitRotationX(rx, x);
    InitRotationY(ry, y);
    InitRotationZ(rz, z);

    m = rz * ry * rx;
}

// Initialize translation matrix
inline void InitTranslation(glm::mat4 &m, float x, float y, float z) {
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
}

// Initialize camera transformation matrix
inline void InitCameraTransform(glm::mat4 &m, glm::vec3 Target, glm::vec3 Up) {
    glm::vec3 N = glm::normalize(Target);

    glm::vec3 UpNorm = Up;
    UpNorm = glm::normalize(UpNorm);

    glm::vec3 U = glm::cross(UpNorm, N);
    U = glm::normalize(U);

    glm::vec3 V = glm::cross(N, U);

    m[0][0] = U.x;
    m[0][1] = U.y;
    m[0][2] = U.z;
    m[0][3] = 0.0f;
    m[1][0] = V.x;
    m[1][1] = V.y;
    m[1][2] = V.z;
    m[1][3] = 0.0f;
    m[2][0] = N.x;
    m[2][1] = N.y;
    m[2][2] = N.z;
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

// Initialize camera matrix with position and target
inline void InitCamera(glm::mat4 &m, glm::vec3 target, glm::vec3 pos, glm::vec3 up) {
    glm::mat4 translation = glm::mat4(1.0);;
    InitTranslation(translation, -pos.x, -pos.y, -pos.z);

    glm::mat4 camMat = glm::mat4(1.0);
    InitCameraTransform(camMat, target, up);
    m = camMat * translation;
}
inline void printMat4(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            aout << matrix[i][j] << " ";
        }
        aout << std::endl;
    }
}
#endif //LEARNOPENGL_MAT4F_H
