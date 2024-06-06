//
// Created by Dark Matter on 5/26/24.
//

#include "Cube.h"
#include "vec2.hpp"
#include "vec3.hpp"

void Cube::generateVertices() {
    float halfSize = size_ / 2.0f;

    glm::vec3 normals[6] = {
            { 0.0f,  0.0f,  1.0f}, // Front
            { 0.0f,  0.0f, -1.0f}, // Back
            {-1.0f,  0.0f,  0.0f}, // Left
            { 1.0f,  0.0f,  0.0f}, // Right
            { 0.0f,  1.0f,  0.0f}, // Top
            { 0.0f, -1.0f,  0.0f}  // Bottom
    };

    glm::vec2 uvs[4] = {
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f}
    };

    vertices_ = {
            // Front face
            Vertex({-halfSize, -halfSize,  halfSize}, uvs[0], normals[0]),
            Vertex({ halfSize, -halfSize,  halfSize}, uvs[1], normals[0]),
            Vertex({ halfSize,  halfSize,  halfSize}, uvs[2], normals[0]),
            Vertex({-halfSize,  halfSize,  halfSize}, uvs[3], normals[0]),

            // Back face
            Vertex({-halfSize, -halfSize, -halfSize}, uvs[0], normals[1]),
            Vertex({ halfSize, -halfSize, -halfSize}, uvs[1], normals[1]),
            Vertex({ halfSize,  halfSize, -halfSize}, uvs[2], normals[1]),
            Vertex({-halfSize,  halfSize, -halfSize}, uvs[3], normals[1]),

            // Left face
            Vertex({-halfSize, -halfSize, -halfSize}, uvs[0], normals[2]),
            Vertex({-halfSize,  halfSize, -halfSize}, uvs[1], normals[2]),
            Vertex({-halfSize,  halfSize,  halfSize}, uvs[2], normals[2]),
            Vertex({-halfSize, -halfSize,  halfSize}, uvs[3], normals[2]),

            // Right face
            Vertex({ halfSize, -halfSize, -halfSize}, uvs[0], normals[3]),
            Vertex({ halfSize,  halfSize, -halfSize}, uvs[1], normals[3]),
            Vertex({ halfSize,  halfSize,  halfSize}, uvs[2], normals[3]),
            Vertex({ halfSize, -halfSize,  halfSize}, uvs[3], normals[3]),

            // Top face
            Vertex({-halfSize,  halfSize, -halfSize}, uvs[0], normals[4]),
            Vertex({ halfSize,  halfSize, -halfSize}, uvs[1], normals[4]),
            Vertex({ halfSize,  halfSize,  halfSize}, uvs[2], normals[4]),
            Vertex({-halfSize,  halfSize,  halfSize}, uvs[3], normals[4]),

            // Bottom face
            Vertex({-halfSize, -halfSize, -halfSize}, uvs[0], normals[5]),
            Vertex({ halfSize, -halfSize, -halfSize}, uvs[1], normals[5]),
            Vertex({ halfSize, -halfSize,  halfSize}, uvs[2], normals[5]),
            Vertex({-halfSize, -halfSize,  halfSize}, uvs[3], normals[5])
    };
}

void Cube::generateIndices() {
    indices_ = {
            // Front face
            0, 1, 2, 2, 3, 0,
            // Back face
            4, 5, 6, 6, 7, 4,
            // Left face
            8, 9, 10, 10, 11, 8,
            // Right face
            12, 13, 14, 14, 15, 12,
            // Top face
            16, 17, 18, 18, 19, 16,
            // Bottom face
            20, 21, 22, 22, 23, 20
    };
}

Cube::Cube(float size, ShaderLoader* shaderLoader) {
    size_ = size;
    generateVertices();
    generateIndices();
    material_ = std::make_shared<Material>(shaderLoader);
}
