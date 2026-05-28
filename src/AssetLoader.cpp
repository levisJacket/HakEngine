#include "AssetLoader.h"
#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using std::string;
using nlohmann::json;

AssetLoader::AssetLoader(string path){
    std::ifstream file(path);
    if (!file.is_open()) {
	std::cerr << "Could not open file\n";
	return;
    }
    paths = json::parse(file);
    file.close();
}


Shader AssetLoader::LoadShader(){
    std::stringstream vertStream;
    std::stringstream fragStream;

    std::ifstream vertFile(paths["vertex"]);
    vertStream << vertFile.rdbuf();
    string vertexStr = vertStream.str();
    const char *vertexSrc = vertexStr.c_str();

    std::ifstream fragFile(paths["fragment"]);
    fragStream << fragFile.rdbuf();
    string fragmentStr = fragStream.str();
    const char *fragmentSrc = fragmentStr.c_str();

    return Shader(vertexSrc,fragmentSrc);
}
