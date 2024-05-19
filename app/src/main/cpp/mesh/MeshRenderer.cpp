//
// Created by Dark Matter on 5/18/24.
//

#include "MeshRenderer.h"
#include "AndroidOut.h"

MeshRenderer::MeshRenderer() {
    transform->SetRotation(0, 0, 0);
    transform->SetPosition(0, 0, 2);
    transform->SetScale(1, 1, 1);
}



void MeshRenderer::render(Mat4f *projectionMatrix) {
    for (const auto &mesh: meshes_) {
        Material* material = mesh->getMaterial();
        Shader* shader  = material->getShader();
        shader->setProjectionMatrix(projectionMatrix);
        shader->bind();

        glBindVertexArray(mesh->getVAO());
        glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_SHORT, (void *)0);
        glBindVertexArray(0);
    }
}

void MeshRenderer::initMesh(Mesh *mesh) const {
    GLuint vao, vbo, ibo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vertex) * mesh->getVertexCount(),
                 mesh->getVertexData(),
                 GL_STATIC_DRAW);
    GLint positionAttrib = mesh->getMaterial()->getShader()->getPositionAttrib();
    glEnableVertexAttribArray(positionAttrib);
    glVertexAttribPointer(
            positionAttrib,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void *) (0)
    );

    GLint uvAttrib = mesh->getMaterial()->getShader()->getUvAttrib();
    glEnableVertexAttribArray(uvAttrib);
    glVertexAttribPointer(
            uvAttrib,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void *) offsetof(Vertex, uv)
    );


    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(Index) * mesh->getIndexCount(),
                 mesh->getIndexData(), GL_STATIC_DRAW);

    mesh->getMaterial()->bindTexture();


    glBindVertexArray(vao);


    mesh->setVAO(vao);
    mesh->setVBO(vbo);
    mesh->setIBO(ibo);

    glBindVertexArray(0);
    glDisableVertexAttribArray(positionAttrib);
    glDisableVertexAttribArray(uvAttrib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshRenderer::onAttach() {
    for (const auto &mesh : meshes_) {
        Material* material = mesh->getMaterial();
        Shader* shader  = material->getShader();
        shader->bind();
    }
}

void MeshRenderer::onCreate() {

}

void MeshRenderer::update() {
    rotation = 0.2;

}

void MeshRenderer::addMesh(const std::shared_ptr<Mesh>& mesh) {
    meshes_.push_back(mesh);
    initMesh(mesh.get());
}

MeshRenderer::~MeshRenderer() {
    aout << "MeshRenderer is destroyed." << std::endl;
}

