#include "Renderer.hpp"
#include <glad/glad.h>
#include <iostream>

Renderer::Renderer(){}

Renderer::Renderer(EntityManager *entityManager, Shader *shader){
    this->entityManager = entityManager;
    this->shader = shader;
}

void Renderer::render(){  
    for(int i = 0; i < entityManager->entityCount; i++ ){
	Entity *entity = entityManager->getEntity(i+1);

	shader->setMat4("u_ModelMatrix", entity->modelMatrix());

	unsigned int VAO = entity->meshVAO();
	unsigned int texture = entity->meshTexture();

	//shader->setInt("u_Texture", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, entity->indexCount(), GL_UNSIGNED_INT, 0);
    }
}
