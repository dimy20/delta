#include "WorldObject.h"
#include "Resources.h"
#include <cfloat>
#include <algorithm>
#include "Math.h"

AABB getAABB(const Model& model){
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
    AABB aabb;
    aabb.min = min;
    aabb.max = max;
    return aabb;
};

void WorldObj::draw(Camera3D& camera){
    BeginMode3D(camera);
    DrawModel(Resources::getModel(mModelId), mPosition, 1.0, WHITE);
    EndMode3D();
}

void WorldObj::drawBoundingBox(Camera3D& camera, Color color){
    AABB aabb = ::getAABB(Resources::getModel(mModelId));
    BeginMode3D(camera);
    Vector3 cubeDims = aabb.max - aabb.min;

    DrawCubeWires(mPosition,
                  std::abs(cubeDims.x),
                  std::abs(cubeDims.y),
                  std::abs(cubeDims.z),
                  color);
    
    EndMode3D();
}

WorldObj::WorldObj(Vector3 position, ModelType modelId){
    mPosition = position;
    mModelId = modelId;
}

AABB WorldObj::getAABB() const {
    return ::getAABB(Resources::getModel(mModelId));
}
