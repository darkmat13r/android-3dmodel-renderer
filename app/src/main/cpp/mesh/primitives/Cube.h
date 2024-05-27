//
// Created by Dark Matter on 5/26/24.
//

#ifndef LEARNOPENGL_CUBE_H
#define LEARNOPENGL_CUBE_H


#include "mesh/Mesh.h"

class Cube : public Mesh{
public :
    Cube(float size);
private:
    float size_;
    void generateVertices();
    void generateIndices();

};


#endif //LEARNOPENGL_CUBE_H
