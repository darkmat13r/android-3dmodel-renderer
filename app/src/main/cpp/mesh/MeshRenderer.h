//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_MESHRENDERER_H
#define LEARNOPENGL_MESHRENDERER_H


#include "Mesh.h"

class MeshRenderer {
public :
    MeshRenderer();
    void render(Mat4f* projectionMatrix);
private :
    std::vector<Mesh> meshes_;
};


#endif //LEARNOPENGL_MESHRENDERER_H
