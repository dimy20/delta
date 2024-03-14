#pragma once

#include <raylib.h>
#include "Resources.h"
#include "Collisions.h"

struct Rotation{
    float angle;
    Vector3 axis;
};

struct GTransform{
    Vector3 position;
    Vector3 scale;
    Vector3 rotationAxis;
    float rotationAngle;
};

struct WorldObj{
    WorldObj(Vector3 position, ModelType modelId);

    ModelType mModelId;

    Vector3 mPosition;
    Vector3 mScale;
    Rotation mRotation;

    void draw(Camera3D& camera);
    void drawBoundingBox(Camera3D& camera, Color color);
    BoundingBox getAABB() const;
    Matrix getTransform() const;
};
