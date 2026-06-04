#pragma once

#include <string>
#include <vector>

class Mesh {
    private:
	unsigned int VBO, VAO, EBO;
	int vertexCount;
    public:
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
	unsigned int GetVBO() const;
	unsigned int GetVAO() const;
	unsigned int GetEBO() const;
	int GetVertexCount();
};
