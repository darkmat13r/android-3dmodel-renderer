//
// Created by Dark Matter on 5/18/24.
//

#include "MeshRenderer.h"

MeshRenderer::MeshRenderer() {
    transform.SetRotation(0,0,0);
    transform.SetPosition(0,0,2);
    transform.SetScale(1,1,1);
}

void MeshRenderer::render(Mat4f *projectionMatrix) {
    for (const auto &material : materials_){
        material->getShader()->setProjectionMatrix(projectionMatrix);
    }
}
