//
// Created by Dark Matter on 5/18/24.
//

#include "Mesh.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Index> indices)
        : vertices_(std::move(vertices)),
          indices_(std::move(indices)) {

}

const Vertex *Mesh::getVertexData() {
    return vertices_.data();
}

const size_t Mesh::getIndexCount() {
    return indices_.size();
}

const Index *Mesh::getIndexData() {
    return indices_.data();
}

