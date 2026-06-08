#include "Renderer.hpp"
#include <glad/glad.h>

Renderer::Renderer(EntityManager *entityManager, Shader *shader){
    this->entityManager = entityManager;
    this->shader = shader;
}

void Renderer::render(){  
    for(int i = 0; i < entityManager->entityCount; i++ ){
	Entity *entity = entityManager->getEntity(i+1);

	shader->setMat4("u_ModelMatrix", entity->modelMatrix());
	unsigned int VAO = entity->meshVAO();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, entity->vertexCount(), GL_UNSIGNED_INT, 0);
    }
}
