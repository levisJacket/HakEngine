#pragma once

#include <string>
#include <vector>

class Mesh {
    private:
	unsigned int VBO, VAO, EBO;
    public:
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
	unsigned int getVBO() const;
	unsigned int getVAO() const;
	unsigned int getEBO() const;
};
