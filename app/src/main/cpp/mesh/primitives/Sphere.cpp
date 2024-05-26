//
// Created by Dark Matter on 5/26/24.
//

#include "Sphere.h"

Sphere::Sphere(float radius, int latitudeSegments,
               int longitudeSegments) {
    radius_ = radius;
    latitudeSegments_ = latitudeSegments;
    longitudeSegments_ = longitudeSegments;
    material_ = std::make_shared<Material>(glm::vec3(1, 0, 0));
    generateVertices();
    generateIndices();
}

void Sphere::generateVertices() {

    for (int lat = 0; lat <= latitudeSegments_; ++lat) {

        double theta = lat * M_PI / latitudeSegments_;
        double sinTheta = sin(theta);
        double cosTheta = cos(theta);

        for (int lon = 0; lon <= longitudeSegments_; ++lon) {
            double phi = lon * 2 * M_PI / longitudeSegments_;

            double sinPhi = sin(phi);
            double cosPhi = cos(phi);

            float x = radius_ * cosPhi * sinTheta;
            float y = radius_ * cosTheta;
            float z = radius_ * sinPhi * sinTheta;

            double length = sqrtf(x * x + y * y + z * z);
            double nx = x / length;
            double ny = y / length;
            double nz = z / length;
            vertices_.emplace_back(glm::vec3(x, y, z), glm::vec3(1), glm::vec3(nx, ny, nz));
        }

    }
}

void Sphere::generateIndices() {

    for (int lat = 0; lat < latitudeSegments_; ++lat) {
        for (int lon = 0; lon < longitudeSegments_; ++lon) {
            int first = lat * (longitudeSegments_ + 1) + lon;
            int second = first + longitudeSegments_ + 1;

            indices_.emplace_back(first);
            indices_.emplace_back(second);
            indices_.emplace_back(first + 1);

            indices_.emplace_back(second);
            indices_.emplace_back(second + 1);
            indices_.emplace_back(first + 1);
        }
    }
}
