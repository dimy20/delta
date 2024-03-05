#pragma once

#include "Resources.h"
#include <raylib.h>

struct AABB{
    Vector3 min;
    Vector3 max;
};

struct WorldObj{
    WorldObj(Vector3 position, ModelType modelId);

    ModelType mModelId;
    Vector3 mPosition;

    void draw(Camera3D& camera);
    void drawBoundingBox(Camera3D& camera, Color color);
    AABB getAABB() const;
};
