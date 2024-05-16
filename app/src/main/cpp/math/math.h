// Created by Dark Matter on 5/8/24.
#include <cmath> // Include cmath for the M_PI constant
#include "vector3.h" // Include the full definition of Vector3

#ifndef LEARNOPENGL_MATH_H
#define LEARNOPENGL_MATH_H

#define ToRadian(degrees) ((degrees) * (M_PI / 180.0))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

union Vector2 {
    struct {
        float x, y;
    };
    struct {
        float u, v;
    };
    float idx[2];
};

struct Vertex {
    constexpr Vertex(const Vector3 &inPosition, const Vector2 &inUV) : position(inPosition), uv(inUV) {}

    Vector3 position;
    Vector2 uv;
};

#endif // LEARNOPENGL_MATH_H
