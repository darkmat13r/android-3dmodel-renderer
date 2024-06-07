//
// Created by Dark Matter on 5/18/24.
//

#include "MeshRenderer.h"
#include "AndroidOut.h"
#include "core/Behaviour.h"
#include "light/DirectionalLight.h"
#include "camera/Camera.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"

MeshRenderer::MeshRenderer() {
    transform->setRotation(0, 0, 0);
    transform->setPosition(0, -2, 4);
    transform->setScale(1, 1, 1);
}


void MeshRenderer::render(Mat4f *projectionMatrix,Camera* camera, Light *light) {
    unsigned int textureN = 0;
    for (const auto &mesh: meshes_) {
        Material *material = mesh->getMaterial();
        Shader *shader = material->getShader();
        shader->setProjectionMatrix(projectionMatrix);
        shader->bind();

        material->bindTexture();

        auto* pDirectionalLight = dynamic_cast<DirectionalLight*>(light);
        if(pDirectionalLight){
            pDirectionalLight->calLocalDirection(*transform);
        }

        auto* pSpotLight = dynamic_cast<SpotLight*>(light);
        if(pSpotLight){

            pSpotLight->calculateDirectionAndPosition(*this->transform);
        }else{
            auto* pPointLight = dynamic_cast<PointLight*>(light);
            if(pPointLight){
                pPointLight->calculateLocalPosition(*this->transform);
            }
        }

        auto cameraLocalPos3f = transform->worldToLocal(camera->transform->position);

        light->bind(shader, cameraLocalPos3f);

        glBindVertexArray(mesh->getVAO());
        glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_SHORT, (void *) 0);
        glBindVertexArray(0);
        material->unbindTexture();
        textureN++;
       // shader->unbind();
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

    GLint normalAttribute = mesh->getMaterial()->getShader()->normalAttribute;
    glEnableVertexAttribArray(normalAttribute);
    glVertexAttribPointer(
            normalAttribute,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void *) offsetof(Vertex, normal)
    );


    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(Index) * mesh->getIndexCount(),
                 mesh->getIndexData(), GL_STATIC_DRAW);

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
    for (const auto &mesh: meshes_) {
        Material *material = mesh->getMaterial();
        Shader *shader = material->getShader();

    }
}

void MeshRenderer::onCreate() {

}


void MeshRenderer::update() {
    rotation = 0.2;

}

void MeshRenderer::addMesh(const std::shared_ptr<Mesh> &mesh) {
    meshes_.push_back(mesh);
    mesh->getMaterial()->getShader()->bind();
    initMesh(mesh.get());
}

MeshRenderer::~MeshRenderer() {
    aout << "MeshRenderer is destroyed." << std::endl;

}

void MeshRenderer::onDestroy() {
    Component::onDestroy();
    for (const auto &mesh: meshes_) {
        Material *material = mesh->getMaterial();
        Shader *shader = material->getShader();
        shader->unbind();
    }
}

