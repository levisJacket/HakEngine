#pragma once

#include "Shader.h"
#include <string>
#include <nlohmann/json.hpp>

class AssetLoader {
private:
    nlohmann::json paths;
public:
    AssetLoader(std::string path);
    Shader LoadShader();
};
