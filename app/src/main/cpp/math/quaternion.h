//
// Created by Dark Matter on 5/15/24.
//

#ifndef LEARNOPENGL_QUATERNION_H
#define LEARNOPENGL_QUATERNION_H

#include "math.h"
#include "vector3.h"
// Forward declaration of Vector3 class to avoid circular dependency
struct Quaternion
{
    float x, y, z, w;
    Quaternion();

    Quaternion(float Angle, const Vector3& V);

    Quaternion(float _x, float _y, float _z, float _w);

    void Normalize();

    Quaternion Conjugate() const;


    Vector3 ToDegrees();
};
Quaternion operator*(const Quaternion& q, const Vector3& v);
Quaternion operator*(const Quaternion& l, const Quaternion& r);
#endif //LEARNOPENGL_QUATERNION_H
