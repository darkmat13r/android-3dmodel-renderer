#ifndef MAT4F_H
#define MAT4F_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

class Mat4f {
public:
    glm::mat4 m;

    // Default constructor initializing to identity matrix
    Mat4f();

    // Parameterized constructor
    Mat4f(float a00, float a01, float a02, float a03,
          float a10, float a11, float a12, float a13,
          float a20, float a21, float a22, float a23,
          float a30, float a31, float a32, float a33);

    // Initialize identity matrix
    void InitIdentity();

    // Initialize scale matrix
    void InitScaleMatrix(float scaleX, float scaleY, float scaleZ);

    // Initialize rotation matrix around X axis
    void InitRotationX(float x);

    // Initialize rotation matrix around Y axis
    void InitRotationY(float y);

    // Initialize rotation matrix around Z axis
    void InitRotationZ(float z);

    // Initialize rotation matrix for combined rotations
    void InitRotationMatrix(float rotationX, float rotationY, float rotationZ);

    // Initialize translation matrix
    void InitTranslation(float x, float y, float z);

    // Initialize camera transformation matrix
    void InitCameraTransform(const glm::vec3 Target, const glm::vec3 Up);

    // Initialize camera matrix with position and target
    void InitCamera(const glm::vec3 target, const glm::vec3 pos, const glm::vec3 up);

    // Create an identity matrix
    static std::unique_ptr<Mat4f> Identity();

    // Matrix multiplication
    Mat4f operator*(const Mat4f& other) const;

    // Function to print the matrix
    void Print() const;
};

// Type alias
using Mat4fAlias = Mat4f;

#endif // MAT4F_H
