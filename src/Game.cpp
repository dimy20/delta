#include "Game.h"
#include "Collisions.h"
#include <raylib.h>
#include <rlgl.h>
#include <cfloat>

Game::Game() {};

int randInt(int start, int end){
    float t = (float)rand() / (float)RAND_MAX;
    return start + (end - start) * t;
};

void Game::initWorldObjects(){

    for(int i = 0; i < 100; i++){
        Vector3 pos;
        pos.x = randInt(-10, 10);
        pos.y = randInt(-10, 10);
        pos.z = randInt(-10, 10);
        m_WorldObjs.push_back(WorldObj(pos, ModelType::DONUT));
    }

    m_WorldObjs.push_back(WorldObj({0.0, 3.0, 0.0}, ModelType::SPHERE));
    m_WorldObjs.push_back(WorldObj({3.0, -1.0, -2.0}, ModelType::DONUT));
};

void Game::init(int w, int h){
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(w, h, "Test");
    SetTargetFPS(60);
    Resources::init();
    mMouseRay.direction = Vector3Zero();
    mMouseRay.position = Vector3Zero();
    mHitInfo.tmax = -1;
    mHitInfo.tmin = -1;

    m_WindowW = w;
    m_WindowH = h;

    initWorldObjects();
    mousePickingClear();
    srand(time(0));

    auto& lightShader = Resources::getShader(ShaderType::LIGHT_SHADER);

    int ambient_color_loc = GetShaderLocation(lightShader, "ambientColor");
    Vector3 ambientColor = (Vector3){1.0, 1.0, 1.0};
    SetShaderValue(lightShader, ambient_color_loc, (const void *)(&ambientColor), SHADER_UNIFORM_VEC3);
};

void Game::quit(){
    Resources::quit();
    CloseWindow();
}

void Game::mousePickingClear(){
    m_MousePickingInfo.m_Name = "None";
    m_MousePickingInfo.m_Collision.distance = FLT_MAX;
    m_MousePickingInfo.m_Collision.hit = false;
};

//Health::Increase(GameObj.health)
void Game::processMousePicking(){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        mousePickingClear();
        for(auto& obj: m_WorldObjs){
            Vector2 mousePosition = GetMousePosition();
            auto bb = obj.getAABB();
            Ray ray = GetMouseRay(mousePosition, mCamera.mRbCam);

            RayCollision boundingBoxCollisionTest;
            boundingBoxCollisionTest = GetRayCollisionBox(ray, bb);

            if(boundingBoxCollisionTest.hit 
                && (boundingBoxCollisionTest.distance < m_MousePickingInfo.m_Collision.distance)){

                m_MousePickingInfo.m_Collision = boundingBoxCollisionTest;
                m_MousePickingInfo.m_Name = "Bounding Box";

                size_t N = Resources::getModel(obj.mModelId).meshCount;

                for(int i = 0; i < N; i++){
                    Mesh& mesh = Resources::getModel(obj.mModelId).meshes[i];
                    RayCollision meshHitInfo = GetRayCollisionMesh(ray,
                                                                   mesh,
                                                                   obj.getTransform());

                    if(meshHitInfo.hit){
                        m_MousePickingInfo.m_Collision = meshHitInfo;
                        m_MousePickingInfo.m_Name = "Mesh";
                        break;
                    }
                }
            }
        }
    }
};

void Game::update(){
    mCamera.update();

    //for(auto& obj : m_WorldObjs){
    //    obj.mRotation.axis = (Vector3){1.0, 0.0, 0.0};
    //}

    if(IsKeyDown(KEY_SPACE)){
        for(auto& obj : m_WorldObjs){
            obj.mRotation.axis = (Vector3){1.0, 0.0, 0.0};
            obj.mRotation.angle += 10.0f;
        }
    }

    processMousePicking();
}

void drawArrow(Vector3 start, Vector3 end, Color color){
    DrawCylinderEx(start, end, 0.02f, 0.02f, 20, color);
    float r = 0.08f;
    Vector3 d = Vector3Normalize(end - start);
    DrawCylinderEx(end, end + d * 0.2f, r, r * 0.1, 20, color);
};

void drawAxes(Camera& camera, WorldObj& obj){
    BeginMode3D(camera);
    Matrix transform = obj.getTransform();
    rlDisableDepthTest();
    drawArrow(obj.mPosition, Vector3Transform((Vector3){1.0, 0.0, 0.0}, transform), RED);
    drawArrow(obj.mPosition, Vector3Transform((Vector3){0.0, 1.0, 0.0}, transform), GREEN);
    drawArrow(obj.mPosition, Vector3Transform((Vector3){0.0, 0.0, 1.0}, transform), BLUE);
    rlEnableDepthTest();
    EndMode3D();
    //DrawLine(0, 0, 100, 100, RED);
};

void drawWorldAxes(Camera& camera){
    BeginMode3D(camera);
    drawArrow(Vector3Zero(), (Vector3){1.0, 0.0, 0.0}, RED);
    drawArrow(Vector3Zero(), (Vector3){0.0, 1.0, 0.0}, GREEN);
    drawArrow(Vector3Zero(), (Vector3){0.0, 0.0, 1.0}, BLUE);
    EndMode3D();
};

void Game::draw(){
    mLight.draw(mCamera.mRbCam);

    for(auto& obj: m_WorldObjs){
        obj.draw(mCamera.mRbCam);
        obj.drawBoundingBox(mCamera.mRbCam, RED);
    };
    
    //Draw grid
    BeginMode3D(mCamera.mRbCam);
    DrawGrid(10, 1.0f);

    /*
    if(mMouseRay.direction != Vector3Zero()){
        DrawLine3D(mMouseRay.position, mMouseRay.position + mMouseRay.direction  * 30.f, GREEN);
    }
    */

    if(mHitInfo.tmin != -1 && mHitInfo.tmax != -1){
        Vector3 minPosition = mMouseRay.position + mMouseRay.direction * mHitInfo.tmin;
        Vector3 maxPosition = mMouseRay.position + mMouseRay.direction * mHitInfo.tmax;

        DrawCube(minPosition, 0.1f, 0.1f, 0.1f, BLUE);
        DrawCube(maxPosition, 0.1f, 0.1f, 0.1f, BLUE);
    }

    EndMode3D();

    drawWorldAxes(mCamera.mRbCam);
    for(auto& obj: m_WorldObjs){
        drawAxes(mCamera.mRbCam, obj);
    }

    auto mousePosition = GetMousePosition();
    DrawText(m_MousePickingInfo.m_Name.c_str(), mousePosition.x + 10, mousePosition.y -20, 16, WHITE);
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

void Light::draw(Camera& camera){
    BeginMode3D(camera);
    DrawCube(mPosition, 1.0, 1.0, 1.0, WHITE);
    EndMode3D();
};
