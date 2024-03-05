#include <raylib.h>
#include <stdio.h>
#include <iostream>
#include <limits>
#include <float.h>
#include <raymath.h>
#include <unordered_map>
#include <vector>
#include "Views.h"
#include "Resources.h"
#include "WorldObject.h"

#define WINDOW_W 1280
#define WINDOW_H 960
#define VECTOR3_ZERO (Vector3){0.0, 0.0, 0.0}

void printRay(Ray * ray){
    printf("Ray(position=(%f, %f, %f), direction=(%f, %f, %f))\n", ray->position.x, ray->position.y, ray->position.z,
           ray->direction.x, ray->direction.y, ray->direction.z);
};

std::vector<Vector3> getGridQuad(float slices, float spacing){
    std::vector<Vector3> ans;

    Vector3 bottomLeftP, bottomRightP, topLeftP, topRightP;
    float gridSize = slices * spacing;
    float halfGridSize = 0.5f * gridSize;

    bottomLeftP.x = -halfGridSize;
    bottomLeftP.y = 0.0f;
    bottomLeftP.z = halfGridSize;

    bottomRightP.x = halfGridSize;
    bottomRightP.y = 0;
    bottomRightP.z = halfGridSize;

    topLeftP.x = -halfGridSize;
    topLeftP.y = 0.0f;
    topLeftP.z = -halfGridSize;

    topRightP.x = halfGridSize;
    topRightP.y = 0.0f;
    topRightP.z = -halfGridSize;

    ans.push_back(bottomLeftP);
    ans.push_back(bottomRightP);
    ans.push_back(topLeftP);
    ans.push_back(topRightP);

    return ans;
};

struct Light{
    Light() : mColor(Vector3One()), mPosition((Vector3){5.0, 10.0f, -2.0f}) {};
    Light(Vector3 position, Vector3 color) : mColor(color), mPosition(position) {};

    Vector3 mColor;
    Vector3 mPosition;
    void draw(Camera& camera);
};

void Light::draw(Camera& camera){
    BeginMode3D(camera);
    DrawCube(mPosition, 1.0, 1.0, 1.0, WHITE);
    EndMode3D();
};

struct Game{
    Game();

    void init();
    void quit();
    void draw();
    void update();
    void run();

    FreeCamera mCamera;
    Light mLight;
    WorldObj mObj;
    Ray mMouseRay;
};

Game::Game() : 
    mObj({5.0, 3.0, 0.0}, ModelType::DONUT)
{

}

void Game::init(){
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(WINDOW_W, WINDOW_H, "Test");
    SetTargetFPS(60);
    Resources::init();
    mMouseRay.direction = Vector3Zero();
    mMouseRay.position = Vector3Zero();

    auto& lightShader = Resources::getShader(ShaderType::LIGHT_SHADER);

    int ambient_color_loc = GetShaderLocation(lightShader, "ambientColor");
    Vector3 ambientColor = (Vector3){1.0, 1.0, 1.0};
    SetShaderValue(lightShader, ambient_color_loc, (const void *)(&ambientColor), SHADER_UNIFORM_VEC3);
};

void Game::quit(){
    Resources::quit();
    CloseWindow();
}

void Game::update(){
    mCamera.update();

    auto quadPoints = getGridQuad(10, 1.0f);
    Ray ray = GetMouseRay(GetMousePosition(), mCamera.mRbCam);
    RayCollision gridHitInfo = GetRayCollisionQuad(ray, quadPoints[0], quadPoints[1], quadPoints[2], quadPoints[3]);

    if(gridHitInfo.hit){
        Vector2 pos = GetMousePosition();
        DrawText("Grid", pos.x + 10, pos.y -20, 16, WHITE);
    }else{
        Vector2 pos = GetMousePosition();
        DrawText("None", pos.x + 10, pos.y -20, 16, WHITE);
    }


    auto obj_aabb = mObj.getAABB();

    BoundingBox b;
    b.max = obj_aabb.max;
    b.min = obj_aabb.min;

    RayCollision objCollisionInfo;
    objCollisionInfo = GetRayCollisionBox(GetMouseRay(GetMousePosition(), mCamera.mRbCam), b);

    if(objCollisionInfo.hit){
        Vector2 pos = GetMousePosition();
        DrawText("Donut", pos.x + 10, pos.y -20, 16, WHITE);
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        mMouseRay = GetMouseRay(GetMousePosition(), mCamera.mRbCam);
    }
}

void Game::draw(){
    mLight.draw(mCamera.mRbCam);
    mObj.draw(mCamera.mRbCam);
    mObj.drawBoundingBox(mCamera.mRbCam, RED);
    
    //Draw grid
    BeginMode3D(mCamera.mRbCam);
    DrawGrid(10, 1.0f);

    if(mMouseRay.direction != Vector3Zero()){
        DrawLine3D(mMouseRay.position, mMouseRay.position + mMouseRay.direction  * 30.f, GREEN);
    }


    EndMode3D();
}

void Game::run(){
    while(!WindowShouldClose()){
        update();
        BeginDrawing();
        ClearBackground(BLACK);
        draw();
        EndDrawing();
    };
}

int main(){
    Game game;
    game.init();
    game.run();
    game.quit();
    return 0;
}
