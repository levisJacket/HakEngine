#include "AssetLoader.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

static std::string PATH = "../PATHS.json";
void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


int main(void)
{
    if (!glfwInit())	{
	std::cout << "Failed to initialize GLFW" << std::endl;
	return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "HakEngine", NULL, NULL);

    if (!window)	{
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))	{
	std::cout << "Failed to initialize GLAD" << std::endl;
	return -1;
    }

    AssetLoader myLoader = AssetLoader(PATH);
    Shader myShader = myLoader.LoadShader();
    
    Mesh myMesh = myLoader.LoadMesh("cube");
    Entity myEntity = Entity(&myMesh);
    
    glm::quat camRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 camLocation = glm::vec3(0.0f, 0.0f, 0.0f);
    Camera myCamera = Camera(0.75f);
    myCamera.setLocation(&camLocation);
    myCamera.setRotation(&camRotation);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    unsigned int VAO;
    while (!glfwWindowShouldClose(window))	{
	glClear(GL_COLOR_BUFFER_BIT);

	myShader.use();

	float timeValue = glfwGetTime();
	float VAR = (timeValue) * 1.0f + 1.0f;;


	myShader.setMat4("modelViewMatrix",myEntity.ModelMatrix() * myCamera.ViewMatrix());

	VAO = myEntity.MeshVAO();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void error_callback(int error, const char* description)	{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)	{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
