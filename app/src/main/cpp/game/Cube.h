//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_CUBE_H
#define LEARNOPENGL_CUBE_H


#include "GameObject.h"
#include "mesh/MeshRenderer.h"

class Cube : public GameObject{
public :
    Cube();
    void render(Mat4f* f) override;
private :
    std::shared_ptr<MeshRenderer> meshRenderer;
};


#endif //LEARNOPENGL_CUBE_H
