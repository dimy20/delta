#pragma once

#include <raylib.h>

enum ShaderType{
    LIGHT_SHADER,
    NUM_SHADERS
};

enum ModelType{
    DONUT,
    NUM_MODELS
};

namespace Resources{
    Shader& getShader(ShaderType id);
    Model& getModel(ModelType id);
    void init();
    void quit();
}

