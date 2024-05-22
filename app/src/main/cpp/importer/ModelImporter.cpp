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

std::shared_ptr<MeshRenderer>
ModelImporter::import(Assimp::Importer *importer, const char *modelPath) {
    std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
    auto aiScene = importer->ReadFile(modelPath, ASSIMP_LOAD_FLAGS);
    aout << "aiScene imported . " << aiScene << std::endl;
    loadMesh(meshRenderer, aiScene, modelPath);
    return meshRenderer;
}

void ModelImporter::loadMesh(std::shared_ptr<MeshRenderer> &meshRenderer,
                             const aiScene *aiScene, const char *modelPath) {
    for (int i = 0; i < aiScene->mNumMeshes; ++i) {
        aiMesh *aiMesh = aiScene->mMeshes[i];
        std::vector<Vertex> vertices;
        std::vector<Index> indices;

        loadSingleMesh(aiMesh, vertices, indices);

        std::shared_ptr<Material> material = loadMaterial(aiScene, aiMesh, modelPath);

        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices,
                                                            material);
        meshRenderer->addMesh(mesh);
    }
}

void ModelImporter::loadSingleMesh(const aiMesh *aiMesh, std::vector<Vertex> &vertices,
                                   std::vector<Index> &indices) {
    const aiVector3D zero(0, 0, 0);
    for (int index = 0; index < aiMesh->mNumVertices; ++index) {
        const aiVector3D &aPos = aiMesh->mVertices[index];
        const aiVector3D &aNormal = aiMesh->mNormals[index];
        const auto aTextCoor = aiMesh->HasTextureCoords(0) ? aiMesh->mTextureCoords[0][index]
                                                           : zero;

        vertices.emplace_back(glm::vec3(aPos.x, aPos.y, aPos.z),
                              glm::vec2(aTextCoor.x, aTextCoor.y),
                              glm::vec3(aNormal.x, aNormal.y, aNormal.z)
        );
    }

    for (int index = 0; index < aiMesh->mNumFaces; ++index) {
        const aiFace &face = aiMesh->mFaces[index];
        assert(face.mNumIndices == 3);
        indices.emplace_back(face.mIndices[0]);
        indices.emplace_back(face.mIndices[1]);
        indices.emplace_back(face.mIndices[2]);
    }


}

std::shared_ptr<Material> ModelImporter::loadMaterial(const aiScene *pScene,
                                                      const aiMesh *aiMesh,
                                                      std::string path) {


    if (pScene->mMaterials) {
        auto aiMaterial = pScene->mMaterials[aiMesh->mMaterialIndex];

        if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            return getDiffuseTexture(aiMaterial, path);
        } else if (aiMaterial->mNumProperties > 0) {
            aiColor3D color(0.f, 0.f, 0.f);
            aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
            return std::make_shared<Material>();
        }

    }
    return std::make_shared<Material>();
}

std::shared_ptr<Material> ModelImporter::getDiffuseTexture(const aiMaterial *aiMaterial,
                                                           std::string path) const {
    aiString materialMath;
    std::string::size_type slashIndex = path.find_last_of("/");
    std::string dir;
    if (slashIndex == std::string::npos) {
        dir = "";
    } else if (slashIndex == 0) {
        dir = "/";
    } else {
        dir = path.substr(0, slashIndex);
    }

    if (aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &materialMath, NULL, NULL, NULL,
                               NULL, NULL) == AI_SUCCESS) {
        std::string p(materialMath.data);

        if (p.substr(0, 2) == ".\\") {
            p = p.substr(2, p.size() - 2);
        }
        std::string fullPath = getStringAfterAssets(p);
        std::string::size_type lastIndex = p.find("assets/");

        if (lastIndex == std::string::npos) {
            fullPath = dir + "/" + p;
        } else {
            fullPath = getStringAfterAssets(p);
        }

        auto texture = TextureAsset::loadAsset(assetManager, fullPath);
        auto material = std::make_shared<Material>(texture);
        material->materialName = fullPath;
        return material;
    }
    return std::make_shared<Material>();
}

std::string ModelImporter::getStringAfterAssets(const std::string &filePath) {
    const std::string target = "assets/";
    size_t pos = filePath.find(target);
    if (pos != std::string::npos) {
        return filePath.substr(pos + target.length());
    }
    return ""; // Return an empty string if "assets" is not found
}

ModelImporter::ModelImporter(AAssetManager *aAssetManager) : assetManager(aAssetManager) {

}


