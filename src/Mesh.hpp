#pragma once

#include <string>
#include <vector>

class Mesh {
    private:
	unsigned int VBO, VAO, EBO, texture;
	int indexCount;
    public:
	Mesh();
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::string texturePath);
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
	unsigned int getVBO() const;
	unsigned int getVAO() const;
	unsigned int getEBO() const;
	unsigned int getTexture() const;
	int getIndexCount();
};
