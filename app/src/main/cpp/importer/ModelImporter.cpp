//
// Created by Dark Matter on 5/17/24.
//

#include "ModelImporter.h"
#include <assimp/port/AndroidJNI/AndroidJNIIOSystem.h>
#include "assimp/Importer.hpp"
#include "utils.h"
#include "AndroidOut.h"
#include "mesh/Mesh.h"
#include "mesh/MeshRenderer.h"

std::shared_ptr<MeshRenderer> ModelImporter::import(Assimp::Importer *importer,  std::shared_ptr<Material> material) {
    std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
    auto aiScene = importer->ReadFile("test_models/untitled.gltf", ASSIMP_LOAD_FLAGS);
    aout << "aiScene imported . " << aiScene << std::endl;
    for (int i = 0; i < aiScene->mNumMeshes; ++i) {
        aiMesh *aiMesh = aiScene->mMeshes[i];
        std::vector<Vertex> vertices;
        std::vector<Index> indices;
        const aiVector3D zero(0, 0, 0);
        for (int index = 0; index < aiMesh->mNumVertices; ++index) {
            const aiVector3D &aPos = aiMesh->mVertices[index];
            const aiVector3D &aNormal = aiMesh->mNormals[index];
            const auto aTextCoor = aiMesh->HasTextureCoords(0) ? aiMesh->mTextureCoords[0][index] : zero;

            vertices.emplace_back(glm::vec3(aPos.x, aPos.y, aPos.z),
                                  glm::vec2(aTextCoor.x, aTextCoor.y),
                                  glm::vec3(aNormal.x, aNormal.y, aNormal.z)
            );
        }

        for (int index = 0; index < aiMesh->mNumFaces; ++index) {
            const aiFace& face = aiMesh->mFaces[index];
            assert(face.mNumIndices == 3);
            indices.emplace_back(face.mIndices[0]);
            indices.emplace_back(face.mIndices[1]);
            indices.emplace_back(face.mIndices[2]);
        }
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices, material);
        meshRenderer->addMesh(mesh);
    }
    return meshRenderer;
}
