#pragma once

#include "Shader.hpp"
#include "Mesh.hpp"
#include <string>
#include <nlohmann/json.hpp>
#include <glm/vec3.hpp>

class AssetLoader {
private:
    nlohmann::json paths;
public:
    AssetLoader(std::string path);
    Shader LoadShader();
    Mesh LoadMesh(std::string name);
};
