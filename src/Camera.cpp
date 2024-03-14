
#include "Views.h"

#include <raymath.h>
#include <string.h>
#include <stdio.h>

#include <raylib.h>
#define DEFAULT_CAMERA_POSITION (Vector3){-11.57, 8.66, 10.00}
#define DEFAULT_PITCH -35.0f
#define DEFAULT_YAW -41.0f

FreeCamera::FreeCamera(){
    mWorldUp = (Vector3){0.0, 1.0, 0.0};
    mUp = mWorldUp;
    mPosition = DEFAULT_CAMERA_POSITION;
    mFront = (Vector3){0.0, 0.0, -1.0};
    mRight = Vector3Zero();
    mSpeed = DEFAULT_CAMERA_SPEED;
    mYaw = DEFAULT_YAW;
    mPitch= DEFAULT_PITCH;
    mSens = 0.1f;
    mFirstTime = true;
    mPrevMousePos = Vector2Zero();
    initRbCamera3D();
}

void FreeCamera::initRbCamera3D(){
    mRbCam.up = mUp;
    mRbCam.fovy = 45.0f;
    mRbCam.position = mPosition;
    mRbCam.projection = CAMERA_PERSPECTIVE;
    mRbCam.target = Vector3Zero();
}

void FreeCamera::update(){
    processKeyInputs();
    processMouseInputs();
    updateVectors();
    updateRbCamera3D();
}

void FreeCamera::updateVectors(){
    //TODO: Only do this whee yaw and pitch actually have changed
    Vec3 newFront;

    newFront.x = std::cos(deg2Radians(mYaw)) * std::cos(deg2Radians(mPitch));
    newFront.y = std::sin(deg2Radians(mPitch));
    newFront.z = std::sin(deg2Radians(mYaw)) * std::cos(deg2Radians(mPitch));

    mFront = Vector3Normalize(newFront);
    mRight = Vector3Normalize(Vector3CrossProduct(mFront, mWorldUp));

    mUp = Vector3Normalize(Vector3CrossProduct(mRight, mFront));
}

void FreeCamera::updateRbCamera3D(){
    mRbCam.position = mPosition;
    mRbCam.target = Vector3Add(mPosition, mFront);
    mRbCam.up = mUp;
}

void FreeCamera::processKeyInputs(){
    if(IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)){
        mPosition = mPosition - (mRight * mSpeed * GetFrameTime());
    }

    if(IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)){
        mPosition = mPosition + (mRight * mSpeed * GetFrameTime());
    }

    if(IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)){
        mPosition = mPosition + (mFront * mSpeed * GetFrameTime());
    }

    if(IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)){
        mPosition = mPosition - (mFront * mSpeed * GetFrameTime());
    }
}

void FreeCamera::processMouseInputs(){
    float xOffset, yOffset;
    Vector2 mousePos = GetMousePosition();

    if(mFirstTime){ // avoid sudden movement when mouse enters screen for the first time
        xOffset = 0.0f;
        yOffset = 0.0f;
        mFirstTime = false;
    }else{
        xOffset = mousePos.x - mPrevMousePos.x;
        yOffset = -(mousePos.y - mPrevMousePos.y);
    }

    mPrevMousePos = mousePos;

    if(IsKeyDown(KEY_LEFT_SHIFT)){
        //scale offsets by sens and update angles
        float yawOffset = xOffset * mSens;
        float pitchOffset = yOffset * mSens;

        mYaw += yawOffset;
        mPitch += pitchOffset;

        if(mPitch > 89.0f) mPitch = 89.0f;
        if(mPitch < -89.0f) mPitch = -89.0f;
    }
}
