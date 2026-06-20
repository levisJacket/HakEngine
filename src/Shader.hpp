#pragma once

#include <glad/glad.h>  
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Shader
{
private:
    unsigned int ID;
    mutable std::unordered_map<std::string, int> uniformLocationCache;

    int getUniformLocation(const std::string &name) const;

public:
    Shader();
    Shader(const char* vertexSource, const char* fragmentSource);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const; 
    void setFloat(const std::string &name, float value) const;

    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat4(const std::string &name, glm::mat4) const;
};
