//
// Created by Dark Matter on 5/18/24.
//

#ifndef LEARNOPENGL_UTILS_H
#define LEARNOPENGL_UTILS_H
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace )


#define COLOR_TEXTURE_UNIT  GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX  0
#define NORMAL_UNIT  GL_TEXTURE1
#define NORMAL_UNIT_INDEX  1
#define SPECULAR_EXPONENT_UNIT  GL_TEXTURE6
#define SPECULAR_EXPONENT_UNIT_INDEX  6


#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#define INVALID_UNIFORM_LOCATION -1

#ifdef ANDROID
#define SNPRINTF snprintf
#endif

#endif //LEARNOPENGL_UTILS_H
