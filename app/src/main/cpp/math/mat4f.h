//
// Created by Dark Matter on 5/16/24.
//

#ifndef LEARNOPENGL_MAT4F_H
#define LEARNOPENGL_MAT4F_H


#include <cmath>
#include <memory>
#include "glm/detail/type_vec3.hpp"
#include "glm/vec3.hpp"
#include "quaternion.h"
#include "vec4.hpp"

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
    glm::vec4 operator*(const glm::vec4 &other) const;

    Mat4f inverse();
};


class Mat3f
{
public:
    float m[3][3];

    Mat3f()  {}

    // Initialize the matrix from the top left corner of the 4-by-4 matrix
    Mat3f(const Mat4f& a)
    {
        m[0][0] = a.m[0][0]; m[0][1] = a.m[0][1]; m[0][2] = a.m[0][2];
        m[1][0] = a.m[1][0]; m[1][1] = a.m[1][1]; m[1][2] = a.m[1][2];
        m[2][0] = a.m[2][0]; m[2][1] = a.m[2][1]; m[2][2] = a.m[2][2];
    }

    glm::vec3 operator*(const glm::vec3& v) const
    {
        glm::vec3 r;

        r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
        r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
        r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;

        return r;
    }

    inline Mat3f operator*(const Mat3f& Right) const
    {
        Mat3f Ret;

        for (unsigned int i = 0 ; i < 3 ; i++) {
            for (unsigned int j = 0 ; j < 3 ; j++) {
                Ret.m[i][j] = m[i][0] * Right.m[0][j] +
                              m[i][1] * Right.m[1][j] +
                              m[i][2] * Right.m[2][j];
            }
        }

        return Ret;
    }

    Mat3f Transpose() const
    {
        Mat3f n;

        for (unsigned int i = 0 ; i < 3 ; i++) {
            for (unsigned int j = 0 ; j < 3 ; j++) {
                n.m[i][j] = m[j][i];
            }
        }

        return n;
    }

    void Print() const
    {
        for (int i = 0 ; i < 3 ; i++) {
            printf("%f %f %f\n", m[i][0], m[i][1], m[i][2]);
        }
    }
};

#endif //LEARNOPENGL_MAT4F_H
