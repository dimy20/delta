#include "WorldObject.h"
#include "Resources.h"

#include <raylib.h>
#include <raymath.h>
#include "Math.h"

void WorldObj::draw(Camera3D& camera){
    BeginMode3D(camera);
    auto& model = Resources::getModel(mModelId);
    DrawModelEx(model, mPosition, mRotation.axis, mRotation.angle, mScale, WHITE);
    EndMode3D();
}

void WorldObj::drawBoundingBox(Camera3D& camera, Color color){
    BeginMode3D(camera);
    DrawBoundingBox(getAABB(), RED);
    EndMode3D();
}

WorldObj::WorldObj(Vector3 position, ModelType modelId){
    mPosition = position;
    mModelId = modelId;
    mScale = (Vector3){1.0, 1.0, 1.0};
    mRotation.axis = (Vector3){0.0, 0.0, 1.0};
    mRotation.angle = 0.0f;
}

#include <cfloat>

Matrix WorldObj::getTransform() const {
    Matrix translation = MatrixTranslate(mPosition.x, mPosition.y, mPosition.z);
    Matrix rotation = MatrixRotate(mRotation.axis, mRotation.angle * DEG2RAD);
    Matrix scale = MatrixScale(mScale.x, mScale.y, mScale.z);
    Matrix T = MatrixMultiply(MatrixMultiply(scale, rotation), translation);
    return T;
}

BoundingBox WorldObj::getAABB() const {
    Matrix T = getTransform();

    Model& model = Resources::getModel(mModelId);

    Mesh& mesh = model.meshes[0];

    float x = mesh.vertices[0];
    float y = mesh.vertices[0+1];
    float z = mesh.vertices[0+2];

    Vector3 min = Vector3Transform({x, y, z}, T);
    Vector3 max = Vector3Transform({x, y, z}, T);

    for(int i = 0; i < mesh.vertexCount * 3; i += 3){
        float x = mesh.vertices[i];
        float y = mesh.vertices[i+1];
        float z = mesh.vertices[i+2];

        Vector3 V = Vector3{x,y,z};

        V = Vector3Transform(V, T);
        
        min.x = std::min(min.x, V.x);
        min.y = std::min(min.y, V.y);
        min.z = std::min(min.z, V.z);

        max.x = std::max(max.x, V.x);
        max.y = std::max(max.y, V.y);
        max.z = std::max(max.z, V.z);
    }

    BoundingBox bb;
    bb.min = min;
    bb.max = max;

    return bb;
}
