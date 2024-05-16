//
// Created by Dark Matter on 5/16/24.
//

#ifndef LEARNOPENGL_VECTOR3_H
#define LEARNOPENGL_VECTOR3_H


union Vector3 {
    struct {
        float x, y, z;
    };
    struct {
        float u, v, w;
    };
    float idx[3];
    Vector3(float pDouble[3]);
    // Constructors
    Vector3(float x, float y, float z);
    Vector3();

    // Member functions
    Vector3 cross(const Vector3& other) const;
    float dot(const Vector3& other) const;
    Vector3 operator*(const float& num) const;
    Vector3 operator+(const Vector3& other) const;
    void operator+=(const Vector3& other);
    void operator-=(const Vector3& other);
    void operator*=(const Vector3& other);
    void operator*=(const float& other);
    void Normalize();
    float Length() const;
    void Rotate(float Angle, const Vector3& V);

};


#endif //LEARNOPENGL_VECTOR3_H
