
#include <math.h>
#include "vector3.h"
#include "quaternion.h"

// Constructor with parameters
Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

// Default constructor
Vector3::Vector3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

// Cross product
Vector3 Vector3::cross(const Vector3& other) const {
    Vector3 newVector(0, 0, 0);
    newVector.x = y * other.z - z * other.y;
    newVector.y = z * other.x - x * other.z;
    newVector.z = x * other.y - y * other.x;
    return newVector;
}

// Dot product
float Vector3::dot(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

// Scalar multiplication
Vector3 Vector3::operator*(const float& num) const {
    return Vector3(x * num, y * num, z * num);
}

// Vector addition
Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

// In-place vector addition
void Vector3::operator+=(const Vector3& other) {
    x = x + other.x;
    y = y + other.y;
    z = z + other.z;
}

// In-place vector subtraction
void Vector3::operator-=(const Vector3& other) {
    x = x - other.x;
    y = y - other.y;
    z = z - other.z;
}

// In-place vector multiplication
void Vector3::operator*=(const Vector3& other) {
    x = x * other.x;
    y = y * other.y;
    z = z * other.z;
}

// In-place scalar multiplication
void Vector3::operator*=(const float& other) {
    x = x * other;
    y = y * other;
    z = z * other;
}

// Normalize the vector
void Vector3::Normalize() {
    float magnitude = Length();
    if (magnitude > 0) {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }
}

// Calculate the length of the vector
float Vector3::Length() const {
    return sqrtf(x * x + y * y + z * z);
}

// Rotate the vector
void Vector3::Rotate(float Angle, const Vector3& V) {
    Quaternion RotationQ(Angle, V);
    Quaternion ConjugateQ = RotationQ.Conjugate();
    Quaternion W = RotationQ * (*this) * ConjugateQ;

    x = W.x;
    y = W.y;
    z = W.z;
}

// Private constructor to initialize with an array
Vector3::Vector3(float pDouble[3]) {
    x = pDouble[0];
    y = pDouble[1];
    z = pDouble[2];
}
