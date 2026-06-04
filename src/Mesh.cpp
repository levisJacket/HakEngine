
#include "Mesh.hpp"

#include <glad/glad.h>

Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices){
    vertexCount = vertices.size();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

unsigned int Mesh::GetVBO() const {
    return VBO;
}

unsigned int Mesh::GetVAO() const {
    return VAO;
}

unsigned int Mesh::GetEBO() const {
    return EBO;
}

int Mesh::GetVertexCount(){
    return vertexCount;
}
