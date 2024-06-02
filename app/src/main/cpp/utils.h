//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_UTILS_H
#define LEARNOPENGL_UTILS_H
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices )


#define COLOR_TEXTURE_UNIT  GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX  0

#define SPECULAR_EXPONENT_UNIT  GL_TEXTURE6
#define SPECULAR_EXPONENT_UNIT_INDEX  6

#endif //LEARNOPENGL_UTILS_H
