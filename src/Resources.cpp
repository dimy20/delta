
#include <cassert>
#include <raylib.h>
#include "Resources.h"
#include <stdio.h>

static Shader shaders[NUM_SHADERS];
static Model models[NUM_MODELS];

Shader& Resources::getShader(ShaderType id){
    assert(id >= 0 && id < NUM_SHADERS);
    return shaders[id];
}

Model& Resources::getModel(ModelType id){
    assert(id >= 0 && id < NUM_MODELS);
    return models[id];
}

void Resources::init(){
    shaders[ShaderType::LIGHT_SHADER] = LoadShader("shaders/vs.glsl", "shaders/fs.glsl");

    models[ModelType::DONUT] = LoadModelFromMesh(GenMeshTorus(0.4, 1.0, 16, 32));
    models[ModelType::CUBE] = LoadModelFromMesh(GenMeshCube(1.0, 1.0, 1.0));
    models[ModelType::TEAPOT] = LoadModel("teapot.obj");
    models[ModelType::SPHERE] = LoadModelFromMesh(GenMeshSphere(1.0, 30, 30));

    for(int i = 0; i < ModelType::NUM_MODELS; i++){
        models[i].materials[0].shader = shaders[ShaderType::LIGHT_SHADER];
    }
}

void Resources::quit(){
    for(int i = 0; i < NUM_SHADERS; i++){ UnloadShader(shaders[i]); }
    for(int i = 0; i < NUM_MODELS; i++){ UnloadModel(models[i]);}
}
