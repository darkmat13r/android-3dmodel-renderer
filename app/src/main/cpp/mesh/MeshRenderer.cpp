//
// Created by Dark Matter on 5/18/24.
//

#include "MeshRenderer.h"

MeshRenderer::MeshRenderer() {

}

void MeshRenderer::render(Mat4f *projectionMatrix) {
    for (const auto &mesh: meshes_){
        mesh.getMaterial()->getShader()->setProjectionMatrix(projectionMatrix);
    }
}
