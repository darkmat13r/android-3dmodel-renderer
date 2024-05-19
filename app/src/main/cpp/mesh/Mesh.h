//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_MESH_H
#define LEARNOPENGL_MESH_H


#include <__memory/shared_ptr.h>
#include "Material.h"

class Mesh {

private :
    std::shared_ptr<std::vector<Material>> materials_;
};


#endif //LEARNOPENGL_MESH_H
