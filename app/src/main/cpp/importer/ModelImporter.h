//
// Created by Dark Matter on 5/17/24.
//

#ifndef LEARNOPENGL_MODELIMPORTER_H
#define LEARNOPENGL_MODELIMPORTER_H


#include "../Model.h"
#include "assimp/Importer.hpp"
#include "mesh/MeshRenderer.h"
#include "assimp/mesh.h"
#include "assimp/material.h"

class ModelImporter {
private:
    AAssetManager *assetManager;
public:
    ModelImporter(AAssetManager *aAssetManager);

    std::shared_ptr<MeshRenderer> import(Assimp::Importer *importer, const char *modelPath);

    void loadMesh(std::shared_ptr<MeshRenderer> &meshRenderer,
                  const aiScene *aiScene, const char *modelPath);

    void loadSingleMesh(const aiMesh *aiMesh, std::vector<Vertex> &vertices,
                        std::vector<Index> &indices);

    std::shared_ptr<Material> loadMaterial(const aiScene *pScene,
                                           const aiMesh *aiMesh,
                                           std::string path);

    static std::string getStringAfterAssets(const std::string &filePath);

    std::shared_ptr<Material> getDiffuseTexture(const aiMaterial *aiMaterial,
                                                std::string path) const;
};


#endif //LEARNOPENGL_MODELIMPORTER_H
