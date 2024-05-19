//
// Created by Dark Matter on 5/18/24.
//

#include "Mesh.h"

#include <utility>


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Index> indices,
           std::shared_ptr<Material> material)
        : vertices_(std::move(vertices)),
          indices_(std::move(indices)), material_(std::move(material)) {

}

 const Vertex *Mesh::getVertexData() const {
    return vertices_.data();
}

 const size_t Mesh::getIndexCount() const {
    return indices_.size();
}

 const Index *Mesh::getIndexData() const {
    return indices_.data();
}

 const size_t Mesh::getVertexCount()  {
    return vertices_.size();
}

GLuint Mesh::getVAO() const { return vao; }

void Mesh::setVAO(GLuint vaoID) { vao = vaoID; }

GLuint Mesh::getVBO() const { return vbo; }

void Mesh::setVBO(GLuint vboID) { vbo = vboID; }

GLuint Mesh::getIBO() const { return ibo; }

void Mesh::setIBO(GLuint iboID) { ibo = iboID; }

Material* Mesh::getMaterial() const{
return material_.get();
}
