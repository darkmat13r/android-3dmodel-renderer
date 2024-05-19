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
     Mesh(
            std::vector<Vertex> vertices,
            std::vector<Index> indices,
            std::shared_ptr<Material> material);


    GLuint getVAO() const;

    void setVAO(GLuint vaoID);

    GLuint getVBO() const;

    void setVBO(GLuint vboID);

    GLuint getIBO() const;

    void setIBO(GLuint iboID);

    const Vertex *getVertexData() const;

    const size_t getIndexCount() const;

    const Index *getIndexData() const;

    const size_t getVertexCount();

    Material *getMaterial() const;
private :
    std::vector<Vertex> vertices_;
    std::vector<Index> indices_;
    std::shared_ptr<Material> material_;
    GLuint vao = -1;
    GLuint vbo = -1;
    GLuint ibo = -1;

};


#endif //LEARNOPENGL_MESH_H
