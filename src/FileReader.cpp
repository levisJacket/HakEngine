#include "FileReader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using std::string;
using nlohmann::json;

ShaderLoader::ShaderLoader(string path){
    std::ifstream file(path);
    if (!file.is_open()) {
	std::cerr << "Could not open file\n";
	return;
    }
    paths = json::parse(file);
    file.close();
}

string ShaderLoader::LoadVertex(){
    std::stringstream stream;
    string path = paths["vertex"];
    std::ifstream shaders(path);
    stream << shaders.rdbuf();
    string vertex = stream.str();
    return vertex;
}

string ShaderLoader::LoadFragment(){
    std::stringstream stream;
    string path = paths["fragment"];
    std::ifstream shaders(path);
    stream << shaders.rdbuf();
    string vertex = stream.str();
    return vertex;
}
