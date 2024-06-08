#include "mat4f.h"
#include "math.h"
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "glm.hpp"

// Default constructor initializing to identity matrix
Mat4f::Mat4f() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

// Parameterized constructor
Mat4f::Mat4f(float a00, float a01, float a02, float a03,
             float a10, float a11, float a12, float a13,
             float a20, float a21, float a22, float a23,
             float a30, float a31, float a32, float a33) {
    m[0][0] = a00;
    m[0][1] = a01;
    m[0][2] = a02;
    m[0][3] = a03;
    m[1][0] = a10;
    m[1][1] = a11;
    m[1][2] = a12;
    m[1][3] = a13;
    m[2][0] = a20;
    m[2][1] = a21;
    m[2][2] = a22;
    m[2][3] = a23;
    m[3][0] = a30;
    m[3][1] = a31;
    m[3][2] = a32;
    m[3][3] = a33;
}

// Initialize scale matrix
void Mat4f::initScaleMatrix(float scaleX, float scaleY, float scaleZ) {
    initIdentity();
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
void Mat4f::initRotationX(float x) {
    initIdentity();
    m[1][1] = cosf(x);
    m[1][2] = sinf(x);
    m[2][1] = -sinf(x);
    m[2][2] = cosf(x);
}

// Initialize rotation matrix around Y axis
void Mat4f::initRotationY(float y) {
    initIdentity();
    m[0][0] = cosf(y);
    m[0][2] = -sinf(y);
    m[2][0] = sinf(y);
    m[2][2] = cosf(y);
}

// Initialize rotation matrix around Z axis
void Mat4f::initRotationZ(float z) {
    initIdentity();
    m[0][0] = cosf(z);
    m[0][1] = sinf(z);
    m[1][0] = -sinf(z);
    m[1][1] = cosf(z);
}

// Initialize rotation matrix for combined rotations
void Mat4f::initRotationMatrix(float rotationX, float rotationY, float rotationZ) {
    Mat4f rx, ry, rz;

    float x = ToRadian(rotationX);
    float y = ToRadian(rotationY);
    float z = ToRadian(rotationZ);

    rx.initRotationX(x);
    ry.initRotationY(y);
    rz.initRotationZ(z);

    *this = rz * ry * rx;
}

// Initialize translation matrix
void Mat4f::initTranslation(float x, float y, float z) {
    initIdentity();
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
}

// Initialize camera transformation matrix
void Mat4f::initCameraTransform(glm::vec3 Target, glm::vec3 Up) {
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
void Mat4f::initCamera(glm::vec3 target, glm::vec3 pos, glm::vec3 up) {
    Mat4f translation;
    translation.initIdentity();
    translation.initTranslation(-pos.x, -pos.y, -pos.z);

    Mat4f camMat;
    camMat.initIdentity();
    camMat.initCameraTransform(target, up);

    *this = camMat * translation;
}

// Initialize camera matrix with position and target
void Mat4f::lookAt(glm::vec3 target, glm::vec3 pos, glm::vec3 up) {
    glm::vec3 forward = glm::normalize(target - pos);
    glm::vec3 right = glm::normalize(glm::cross(glm::normalize(up), forward));
    glm::vec3  cameraUp = glm::cross(forward, right);

    Mat4f translation;
    translation.initTranslation(-pos.x, -pos.y, -pos.z);

    // Create a rotation matrix to align the camera's axes with the world's axes
    Mat4f rotation;
    rotation.initIdentity();
    rotation.m[0][0] = right.x;
    rotation.m[0][1] = right.y;
    rotation.m[0][2] = right.z;
    rotation.m[1][0] = cameraUp.x;
    rotation.m[1][1] = cameraUp.y;
    rotation.m[1][2] = cameraUp.z;
    rotation.m[2][0] = forward.x;
    rotation.m[2][1] = forward.y;
    rotation.m[2][2] = forward.z;

    *this = rotation * translation;
}

// Initialize identity matrix
void Mat4f::initIdentity() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

// Create an identity matrix
std::unique_ptr<Mat4f> Mat4f::Identity() {
    return std::unique_ptr<Mat4f>(new Mat4f());
}

// Matrix multiplication
Mat4f Mat4f::operator*(const Mat4f &other) const {
    Mat4f ret;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ret.m[i][j] = m[i][0] * other.m[0][j] +
                          m[i][1] * other.m[1][j] +
                          m[i][2] * other.m[2][j] +
                          m[i][3] * other.m[3][j];
        }
    }
    return ret;
}

// Matrix multiplication
glm::vec4 Mat4f::operator*(const glm::vec4 &other) const {
    glm::vec4 ret;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ret[j] = m[i][0] * other[0] +
                     m[i][1] * other[1] +
                     m[i][2] * other[2] +
                     m[i][3] * other[3];
        }
    }
    return ret;
}

Mat4f Mat4f::inverse() {
    Mat4f invMat;
    glm::mat4 mat = glm::mat4(1.0);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            mat[i][j] = this->m[i][j];
        }
    }
    mat = glm::inverse(mat);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            invMat.m[i][j] = mat[i][j];
        }
    }
    return invMat;
}
