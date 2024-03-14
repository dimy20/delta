#pragma once
#include <raylib.h>

struct HitInfo{
    float tmin;
    float tmax;
};

struct AABB{
    AABB();
    AABB(const Model& model);

    bool isHit(Vector3 rayOrigin, Vector3 rayDirection, HitInfo& hitInfo);

    Vector3 mMin;
    Vector3 mMax;
};
