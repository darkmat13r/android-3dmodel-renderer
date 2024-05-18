//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_MESHRENDERER_H
#define LEARNOPENGL_MESHRENDERER_H


#include "Mesh.h"
#include "core/Component.h"

class MeshRenderer : public Component {
public :
    MeshRenderer();

    void render(Mat4f *f) override;

private :
    std::vector<Material*> materials_;
    std::vector<Mesh> meshes_;
};


#endif //LEARNOPENGL_MESHRENDERER_H
