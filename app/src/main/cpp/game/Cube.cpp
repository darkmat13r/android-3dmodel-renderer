//
// Created by Dark Matter on 5/18/24.
//

#include "Cube.h"

Cube::Cube() {
    meshRenderer = std::make_shared<MeshRenderer>();

}


void Cube::render(Mat4f* f) {
    meshRenderer->render(f);
}