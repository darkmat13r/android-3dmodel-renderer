//
// Created by Dark Matter on 5/8/24.
//

#ifndef LEARNOPENGL_TRANSFORM_H
#define LEARNOPENGL_TRANSFORM_H

#include <vector>
#include "../math/math.h"
#include "../math/mat4f.h"
#include "../math/quaternion.h"

class Transform {
public :
    Transform();
    void setScale(float scaleX, float scaleY, float scaleZ);
    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void rotate(float x, float y, float z);
    Mat4f matrix();

private:
    glm::vec3 position_;
    Quaternion rotation_;
    glm::vec3 scale_;
};


#endif //LEARNOPENGL_TRANSFORM_H
