#include "Collisions.h"
#include "Math.h"
#include <raylib.h>
#include <raymath.h>
#include <cfloat>
#include <algorithm>
#include <iostream>

AABB::AABB(){
    mMin = Vector3Zero();
    mMax = Vector3Zero();
}

AABB::AABB(const Model& model){
    Mesh& mesh = model.meshes[0];

    Vector3 min = {FLT_MAX, FLT_MAX, FLT_MAX};
    Vector3 max = {FLT_MIN, FLT_MIN, FLT_MIN};

    for(int i = 0; i < mesh.vertexCount * 3; i += 3){
        float x = mesh.vertices[i];
        float y = mesh.vertices[i+1];
        float z = mesh.vertices[i+2];
        
        min.x = std::min(min.x, x);
        min.y = std::min(min.y, y);
        min.z = std::min(min.z, z);

        max.x = std::max(max.x, x);
        max.y = std::max(max.y, y);
        max.z = std::max(max.z, z);
    }
    mMin = min;
    mMax = max;
}

bool AABB::isHit(Vector3 rayOrigin, Vector3 rayDirection, HitInfo& hitInfo){
    /* t's for intersections with planes defined by minimum  and max bounds of the box */
    Vector3 tminPlanes = Vector3Zero(); 
    Vector3 tmaxPlanes = Vector3Zero();

    //solve t's for all planes defined by the minimum bounds of the box
    tminPlanes = (mMin - rayOrigin) / rayDirection;
    //solve t's for all planes defined by the max bounds of the box
    tmaxPlanes = (mMax - rayOrigin) / rayDirection;

    //top view
    hitInfo.tmin = std::max(tminPlanes.x, tminPlanes.z);
    hitInfo.tmax = std::min(tmaxPlanes.z, tmaxPlanes.x);

    //side view
    //float tmin = std::max({tminPlanes.z, tminPlanes.y, tminPlanes.x});
    //float tmax = std::max({tmaxPlanes.z, tmaxPlanes.y, tmaxPlanes.x});

    //hitInfo.tmin = tmin;


    return true;
}

