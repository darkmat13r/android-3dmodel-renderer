#include "Utility.h"
#include "AndroidOut.h"
#include "math/mat4f.h"
#include "math/math.h"

#include <GLES3/gl3.h>



Mat4f *
Utility::buildOrthographicMatrix(Mat4f *outMatrix, float halfHeight, float aspect, float near,
                                 float far) {
    float halfWidth = halfHeight * aspect;

    float A = -2.f / (far - near);
    float B = -(far + near) / (far - near);
    outMatrix->InitIdentity();
    outMatrix->m[0][0] = 1/aspect;
    outMatrix->m[1][1] = 1/aspect;
    outMatrix->m[2][2] = A;
    outMatrix->m[2][3] = B;
    outMatrix->m[3][3] = 0;
    outMatrix->m[3][2] = 1;

    return outMatrix;
}
Mat4f *
Utility::buildPerspectiveMat(Mat4f *outMatrix, float halfHeight, float aspect, float near,
                             float far) {
    float pov = 90;
    float tan = tanf(ToRadian(pov / 2));
    float halfWidth = halfHeight * aspect;
    float d = 1/tan;
    float zRange = (near - far);
    float A = (-far - near) / zRange;
    float B = 2 * far * near / zRange;
    outMatrix->InitIdentity();
    outMatrix->m[0][0] = d/aspect;
    outMatrix->m[1][1] = d;
    outMatrix->m[2][2] = A;
    outMatrix->m[2][3] = B;
    outMatrix->m[3][3] = 0;
    outMatrix->m[3][2] = 1;

    return outMatrix;
}

float *Utility::buildIdentityMatrix(float *outMatrix) {
    // column 1
    outMatrix[0] = 1.f;
    outMatrix[1] = 0.f;
    outMatrix[2] = 0.f;
    outMatrix[3] = 0.f;

    // column 2
    outMatrix[4] = 0.f;
    outMatrix[5] = 1.f;
    outMatrix[6] = 0.f;
    outMatrix[7] = 0.f;

    // column 3
    outMatrix[8] = 0.f;
    outMatrix[9] = 0.f;
    outMatrix[10] = 1.f;
    outMatrix[11] = 0.f;

    // column 4
    outMatrix[12] = 0.f;
    outMatrix[13] = 0.f;
    outMatrix[14] = 0.f;
    outMatrix[15] = 1.f;

    return outMatrix;
}