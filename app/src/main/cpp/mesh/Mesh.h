//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_MESH_H
#define LEARNOPENGL_MESH_H


#include "Material.h"
#include "math/math.h"
#include "Model.h"
#include <vector>
class Mesh {
public:
    inline Mesh(
            std::vector<Vertex> vertices,
    std::vector<Index> indices);

    inline const Vertex *getVertexData() ;

    inline const size_t getIndexCount();

    inline const Index *getIndexData();

    inline size_t getVertexCount() ;

private :
    std::vector<Vertex> vertices_;
    std::vector<Index> indices_;
    GLuint vao = -1;
    GLuint vbo = -1;
    GLuint ibo = -1;
};


#endif //LEARNOPENGL_MESH_H
