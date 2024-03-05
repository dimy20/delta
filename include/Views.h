#pragma once

#define DEFAULT_CAMERA_SPEED 5.0f
#include <raylib.h>
#include "Math.h"

struct FreeCamera{
    FreeCamera();
    void update();

    private:
        void initRbCamera3D();

        void processKeyInputs();
        void processMouseInputs();
        void updateVectors();

        void updateRbCamera3D();

    public:
        Camera3D mRbCam;

        Vec3 mPosition;
        Vec3 mUp;
        Vec3 mWorldUp;
        Vec3 mFront;
        Vec3 mRight;

        float mSpeed;
        float mYaw;
        float mPitch;
        float mSens;
        bool mFirstTime;
        Vector2 mPrevMousePos;
};
