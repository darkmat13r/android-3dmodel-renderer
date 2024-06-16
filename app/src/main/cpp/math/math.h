// Created by Dark Matter on 5/8/24.
#include <cmath> // Include cmath for the M_PI constant
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#ifndef LEARNOPENGL_MATH_H
#define LEARNOPENGL_MATH_H

#define ToRadian(degrees) ((degrees) * (M_PI / 180.0))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

struct Vertex {
    constexpr Vertex(const glm::vec3 &inPosition,
                     const glm::vec2 &inUV, const glm::vec3  &tangent)
            : position(inPosition),
              uv(inUV), normal(glm::vec3{}), tangent(tangent) {};

    constexpr Vertex(const glm::vec3 &inPosition,
                     const glm::vec2 &inUV,
                     const glm::vec3 &inNormal, const glm::vec3  &tangent)
            : position(inPosition),
                uv(inUV), normal(inNormal), tangent(tangent) {}

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 tangent;
    glm::vec3 biTangent;
};

#endif // LEARNOPENGL_MATH_H
