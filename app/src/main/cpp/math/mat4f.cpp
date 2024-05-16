#include "mat4f.h"

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
    m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
    m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
    m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
    m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
}

// Initialize scale matrix
void Mat4f::InitScaleMatrix(float scaleX, float scaleY, float scaleZ) {
    InitIdentity();
    m[0][0] = scaleX; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
    m[1][0] = 0.0f;   m[1][1] = scaleY; m[1][2] = 0.0f;   m[1][3] = 0.0f;
    m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = scaleZ; m[2][3] = 0.0f;
    m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
}

// Initialize rotation matrix around X axis
void Mat4f::InitRotationX(float x) {
    InitIdentity();
    m[1][1] = cosf(x); m[1][2] = sinf(x);
    m[2][1] = -sinf(x); m[2][2] = cosf(x);
}

// Initialize rotation matrix around Y axis
void Mat4f::InitRotationY(float y) {
    InitIdentity();
    m[0][0] = cosf(y); m[0][2] = -sinf(y);
    m[2][0] = sinf(y); m[2][2] = cosf(y);
}

// Initialize rotation matrix around Z axis
void Mat4f::InitRotationZ(float z) {
    InitIdentity();
    m[0][0] = cosf(z); m[0][1] = sinf(z);
    m[1][0] = -sinf(z); m[1][1] = cosf(z);
}

// Initialize rotation matrix for combined rotations
void Mat4f::InitRotationMatrix(float rotationX, float rotationY, float rotationZ) {
    Mat4f rx, ry, rz;

    float x = rotationX * M_PI / 180.0f;
    float y = rotationY * M_PI / 180.0f;
    float z = rotationZ * M_PI / 180.0f;

    rx.InitRotationX(x);
    ry.InitRotationY(y);
    rz.InitRotationZ(z);

    *this = rz * ry * rx;
}

// Initialize translation matrix
void Mat4f::InitTranslation(float x, float y, float z) {
    InitIdentity();
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
}

// Initialize camera transformation matrix
void Mat4f::InitCameraTransform(Vector3 Target, Vector3 Up) {
    Vector3 N = Target;
    N.Normalize();

    Vector3 UpNorm = Up;
    UpNorm.Normalize();

    Vector3 U = UpNorm.cross(N);
    U.Normalize();

    Vector3 V = N.cross(U);

    m[0][0] = U.x; m[0][1] = U.y; m[0][2] = U.z; m[0][3] = 0.0f;
    m[1][0] = V.x; m[1][1] = V.y; m[1][2] = V.z; m[1][3] = 0.0f;
    m[2][0] = N.x; m[2][1] = N.y; m[2][2] = N.z; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

// Initialize camera matrix with position and target
void Mat4f::InitCamera(Vector3 target, Vector3 pos, Vector3 up) {
    Mat4f translation;
    translation.InitIdentity();
    translation.InitTranslation(-pos.x, -pos.y, -pos.z);

    Mat4f camMat;
    camMat.InitIdentity();
    camMat.InitCameraTransform(target, up);

    *this = camMat * translation;
}

// Initialize identity matrix
void Mat4f::InitIdentity() {
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
