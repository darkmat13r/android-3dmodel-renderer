//
// Created by Dark Matter on 5/26/24.
//

#ifndef LEARNOPENGL_SPHERE_H
#define LEARNOPENGL_SPHERE_H


#include "mesh/Mesh.h"

class Sphere : public Mesh {
public :
    Sphere(float radius, int latitudeSegments,
           int longitudeSegments, ShaderLoader* shaderLoader);

private:
    float radius_;
    int latitudeSegments_;
    int longitudeSegments_;
    void generateVertices();
    void generateIndices();
};


#endif //LEARNOPENGL_SPHERE_H
