#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(){}

Shader::Shader(const char* vertexSource, const char* fragmentSource){
    int success;
    char infoLog[512];

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
	glGetProgramInfoLog(ID, 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
};
    
void Shader::use(){
    glUseProgram(ID);
};

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(getUniformLocation(name), (int)value);
};

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(getUniformLocation(name), value);
};

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(getUniformLocation(name), value);
};

void Shader::setVec2(const std::string &name, float x, float y) const {
     glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
     glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const {
     glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
     glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setMat4(const std::string &name, glm::mat4 mat) const {
    const float* floatPtr = glm::value_ptr(mat);
    glUniformMatrix4fv(getUniformLocation(name), 1, 0, floatPtr);
}

int Shader::getUniformLocation(const std::string &name) const{
    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
	return uniformLocationCache[name];
    }

    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
	std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }
    
    uniformLocationCache[name] = location;
    return location;
};
