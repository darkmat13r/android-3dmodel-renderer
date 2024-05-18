//
// Created by Dark Matter on 5/15/24.
//

#ifndef LEARNOPENGL_QUATERNION_H
#define LEARNOPENGL_QUATERNION_H

#include "glm/vec3.hpp"

// Forward declaration of Vector3 class to avoid circular dependency
struct Quaternion
{
    float x, y, z, w;
    Quaternion();

    Quaternion(float Angle, const glm::vec3& V);

    Quaternion(float _x, float _y, float _z, float _w);

    void Normalize();

    Quaternion Conjugate() const;


    glm::vec3 ToDegrees();

};
Quaternion operator*(const Quaternion& q, glm::vec<3, float,(glm::qualifier)0> v);
Quaternion operator*(const Quaternion& l, const Quaternion& r);

#endif //LEARNOPENGL_QUATERNION_H
