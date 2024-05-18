//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_MESH_H
#define LEARNOPENGL_MESH_H


#include "Material.h"
#include <vector>
class Mesh {
public:
    Material* getMaterial() const;
private :
    std::shared_ptr<Material*> material_;
};


#endif //LEARNOPENGL_MESH_H
