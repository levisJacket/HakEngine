#pragma once

#include "Shader.hpp"
#include "Mesh.hpp"
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <glm/vec3.hpp>

class AssetLoader {
private:
    mutable std::unordered_map<std::string, Mesh> meshMap;
    nlohmann::json paths;
public:
    AssetLoader(std::string path);
    Shader loadShader();
    Mesh* loadMesh(std::string name);
};
