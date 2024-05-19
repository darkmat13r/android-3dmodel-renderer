//
// Created by Dark Matter on 5/17/24.
//

#ifndef LEARNOPENGL_MODELIMPORTER_H
#define LEARNOPENGL_MODELIMPORTER_H


#include "../Model.h"
#include "assimp/Importer.hpp"
#include "mesh/MeshRenderer.h"

class ModelImporter {
public:
    static std::shared_ptr<MeshRenderer> import(Assimp::Importer *importer, std::shared_ptr<Material> material);
};


#endif //LEARNOPENGL_MODELIMPORTER_H
