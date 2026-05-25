#pragma once
#include <string>
#include <nlohmann/json.hpp>

class ShaderLoader {
private:
    nlohmann::json paths;
public:
    ShaderLoader(std::string path);
    std::string LoadVertex();
};
