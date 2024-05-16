//
// Created by Dark Matter on 5/13/24.
//

#ifndef LEARNOPENGL_CAMERA_H
#define LEARNOPENGL_CAMERA_H


#include "GameObject.h"

class Camera : public GameObject {

public:
    Camera(int WindowWidth, int WindowHeight, const Vector3& Pos, const Vector3& Target, const Vector3& Up);
    void Init();

    void SetPosition(float x, float y, float z);
    void OnUp();
    void Update();
    void OnDown();
    void OnLeft();
    void OnRight();
    void OnMove(int DeltaX, int deltaY);
    void OnMove();
    void OnZoomIn();
    void OnRender();
    void OnZoomOut();
    void PanUp();
    void PanDown();
    Mat4f Matrix();

private :
    Vector3 target_;
    Vector3 pos_;
    Vector3 up_;
    float speed_ = 0.2f;
    int m_windowWidth;
    int m_windowHeight;

    float m_AngleH;
    float m_AngleV;

    bool m_OnUpperEdge;
    bool m_OnLowerEdge;
    bool m_OnLeftEdge;
    bool m_OnRightEdge;

};


#endif //LEARNOPENGL_CAMERA_H
