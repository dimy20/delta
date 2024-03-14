#pragma once

#include "Collisions.h"
#include "Views.h"
#include "Resources.h"
#include "WorldObject.h"
#include <vector>

struct Light{
    Light() : mColor(Vector3One()), mPosition((Vector3){5.0, 10.0f, -2.0f}) {};
    Light(Vector3 position, Vector3 color) : mColor(color), mPosition(position) {};

    Vector3 mColor;
    Vector3 mPosition;
    void draw(Camera& camera);
};

struct MousePickingInfo{
    std::string m_Name;
    RayCollision m_Collision;
    Vector2 m_MousePosition;
};

struct Game{
    Game();

    void init(int w, int h);
    void quit();
    void draw();
    void update();
    void run();

    void processMousePicking();
    void mousePickingClear();
    void initWorldObjects();

    FreeCamera mCamera;
    Light mLight;

    std::vector<WorldObj> m_WorldObjs;

    Ray mMouseRay;
    HitInfo mHitInfo;

    int m_WindowW;
    int m_WindowH;

    MousePickingInfo m_MousePickingInfo;
};
