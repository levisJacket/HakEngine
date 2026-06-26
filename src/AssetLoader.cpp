#include "AssetLoader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using std::string;
using nlohmann::json;

AssetLoader::AssetLoader(){}
AssetLoader::AssetLoader(std::string path){
    std::ifstream file(path);
    if (!file.is_open()) {
	std::cerr << "Could not open file\n";
	return;
    }
    paths = json::parse(file);
    file.close();

    meshDir = paths["mesh"];
}

Shader AssetLoader::loadShader(){
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

Mesh* AssetLoader::loadMesh(std::string name){
    if (meshMap.find(name) != meshMap.end()){
	return &meshMap[name];
    }

    string fileName = meshDir + name;
    std::ifstream File(fileName);
    std::stringstream Stream;
    Stream << File.rdbuf();

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    string line;
    int index = 0;
    float x, y, z;

    while (std::getline(Stream,line)) {
	std::stringstream ss(line);
	string word;	ss >> word;
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
	    vertices.push_back(0.0f);
	    vertices.push_back(0.0f);
	    indices.push_back(index++);
	}
    }
    meshMap[name] = Mesh(vertices, indices);
    return &meshMap[name];
}

Mesh* AssetLoader::loadMesh(std::string name, std::string texture){
    if (meshMap.find(name) != meshMap.end()){
	return &meshMap[name];
    }

    string fileName = meshDir + name;
    std::ifstream File(fileName);
    std::stringstream Stream;
    Stream << File.rdbuf();

    std::vector<float> v;
    std::vector<float> vn;
    std::vector<float> vt;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    string line;
    float x, y, z;

    while (std::getline(Stream,line)) {
	std::stringstream ss(line);
	string word;	ss >> word;
	if (word == "v"){
	    float val;
	    ss >> val;	v.push_back(val);
	    ss >> val;	v.push_back(val);
	    ss >> val;	v.push_back(val);
	} else if (word == "vn"){
	    float val;
	    ss >> val;	vn.push_back(val);
	    ss >> val;	vn.push_back(val);
	    ss >> val;	vn.push_back(val);
	} else if (word == "vt"){
	    float val;
	    ss >> val;	vt.push_back(val);
	    ss >> val;	vt.push_back(val);
	} else if (word == "f"){
	    string vert;
	    string val;
	    int vIndex, vtIndex, vnIndex;
	    
	    int vertexIndex = vertices.size() / 8;
	    int vertexCount = 0;
	    while (ss >> vert){
		std::stringstream vertStream(vert); 
		
		if (getline(vertStream, val, '/')) {
		    int vID = std::stoi(val);
		    vIndex = (vID - 1) * 3;
		}

		if (getline(vertStream, val, '/')) {
		    int vtID = std::stoi(val);
		    vtIndex = (vtID - 1) * 2;
		}

		if (getline(vertStream, val, '/')) {
		    int vnID = std::stoi(val);
		    vnIndex = (vnID - 1) * 3;
		}

		vertices.push_back(v[vIndex]);
		vertices.push_back(v[vIndex + 1]);
		vertices.push_back(v[vIndex + 2]);

		vertices.push_back(vn[vnIndex]);
		vertices.push_back(vn[vnIndex + 1]);
		vertices.push_back(vn[vnIndex + 2]);

		vertices.push_back(vt[vtIndex]);
		vertices.push_back(vt[vtIndex + 1]);

		vertexCount++;
	    }
	    for (int i = 2; i < vertexCount; i++){
		indices.push_back(vertexIndex);
		indices.push_back(vertexIndex + i - 1);
		indices.push_back(vertexIndex + i);
	    }
	}
    }

    meshMap[name] = Mesh(vertices, indices, meshDir + texture);
    return &meshMap[name];
}
