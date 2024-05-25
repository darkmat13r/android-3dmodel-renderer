#ifndef ANDROIDGLINVESTIGATIONS_MODEL_H
#define ANDROIDGLINVESTIGATIONS_MODEL_H

#include <vector>
#include "TextureAsset.h"
#include "math/math.h"
#include "transform/Transform.h"
#include "core/Component.h"

typedef uint16_t Index;

class Model : public Component{
public:

    inline Model(
            std::vector<Vertex> vertices,
            std::vector<Index> indices,
            std::shared_ptr<TextureAsset> spTexture)
            : vertices_(std::move(vertices)),
              indices_(std::move(indices)),
              spTexture_(std::move(spTexture)){
        transform->setRotation(0, 0, 0);
        transform->setPosition(0, 0, 2);
        transform->setScale(1, 1, 1);
    }

    inline const Vertex *getVertexData() const {
        return vertices_.data();
    }

    inline const size_t getIndexCount() const {
        return indices_.size();
    }

    inline const Index *getIndexData() const {
        return indices_.data();
    }

    inline const TextureAsset &getTexture() const {
        return *spTexture_;
    }

    inline size_t getVertexCount() const {
        return vertices_.size();
    }

    GLuint getVAO() const { return vao; }
    void setVAO(GLuint vaoID) { vao = vaoID; }
    GLuint getVBO() const { return vbo; }
    void setVBO(GLuint vboID) { vbo = vboID; }
    GLuint getIBO() const { return ibo; }
    void setIBO(GLuint iboID) { ibo = iboID; }

private:
    std::vector<Vertex> vertices_;
    std::vector<Index> indices_;
    std::shared_ptr<TextureAsset> spTexture_;
    GLuint vao = -1;
    GLuint vbo = -1;
    GLuint ibo = -1;

};

#endif //ANDROIDGLINVESTIGATIONS_MODEL_H