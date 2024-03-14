#include <cwchar>
#include <raylib.h>
#include <stdio.h>
#include <iostream>
#include <limits>
#include <float.h>
#include <raymath.h>
#include <unordered_map>
#include <vector>

#include "Game.h"

#define WINDOW_W 1280
#define WINDOW_H 960
#define VECTOR3_ZERO (Vector3){0.0, 0.0, 0.0}

#define XAXIS (Vector3){1.0, 0.0, 0.0}
#define YAXIS (Vector3){0.0, 1.0, 0.0}
#define ZAXIS (Vector3){1.0, 0.0, 1.0}

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

int main(){
    Game game;
    game.init(WINDOW_W, WINDOW_H);
    game.run();
    game.quit();
    return 0;
}
