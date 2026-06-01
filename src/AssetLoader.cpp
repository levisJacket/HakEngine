#include "AssetLoader.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
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

Mesh AssetLoader::LoadMesh(std::string name){
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    std::string fileName = paths["mesh"][name];
    std::ifstream File(fileName);
    std::stringstream Stream;
    Stream << File.rdbuf();

    std::string line;
    int index = 0;
    float x, y, z;
    while (std::getline(Stream,line)) {
	std::stringstream ss(line);
	std::string word;	ss >> word;
	if (word == "facet"){
	    ss >> word;
	    ss >> x;	ss >> y;	ss >> z;
	    continue;
	}
	if (word == "vertex"){
	    float val;
	    ss >> val;	vertices.push_back(val);
	    ss >> val;	vertices.push_back(val);
	    ss >> val;	vertices.push_back(val);
	    vertices.push_back(x);
	    vertices.push_back(y);
	    vertices.push_back(z);
	    indices.push_back(index++);
	}
    }

    return Mesh(vertices, indices);
}
