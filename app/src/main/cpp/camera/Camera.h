//
// Created by Dark Matter on 5/13/24.
//


#include "../core/Component.h"
#include "math/quaternion.h"
#include "vec4.hpp"

#ifndef LEARNOPENGL_CAMERA_H
#define LEARNOPENGL_CAMERA_H


class Camera : public Component {

public:
    Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);
    void init();

    void setPosition(float x, float y, float z);
    void onUp();
    void update();
    void onDown();
    void onLeft();
    void onRight();
    void onMove(float deltaX, float deltaY);
    void moveForward(float distance);
    void moveLeft(float distance);
    void moveUp(float distance);
    void onMove();
    void onZoomIn();
    void onRender();
    void onZoomOut();
    void panUp();
    void panDown();
    Mat4f matrix();

    static void rotate(float Angle, const glm::vec3& V, glm::vec3& target);

    glm::vec3& getPos();

    glm::vec3 getTarget();

    void setTarget(const glm::vec3& target);

private :
    glm::vec3 target_{};
    glm::vec3 up_{};
    float speed_ = 3;
    float angleX = 0;
    float angleY = 0;
    float m_AngleH{};
    float m_AngleV{};

    bool m_OnUpperEdge{};
    bool m_OnLowerEdge{};
    bool m_OnLeftEdge{};
    bool m_OnRightEdge{};

};
#endif //LEARNOPENGL_CAMERA_H
