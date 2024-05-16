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
    Transform() : position_(0, 0, 0), rotation_(0, Vector3(0, 0, 0)), scale_(1, 1, 1) {}
    void SetScale(float scaleX, float scaleY, float scaleZ);
    void SetPosition(float x, float y, float z);
    void SetRotation(float x, float y, float z);
    void Rotate(float x, float y, float z);
    Mat4f Matrix();

private:
    Vector3 position_;
    Quaternion rotation_;
    Vector3 scale_;
};


#endif //LEARNOPENGL_TRANSFORM_H
