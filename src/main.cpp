#include "AssetLoader.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "Light.hpp"
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    AssetLoader myLoader = AssetLoader(PATH);
    Shader myShader = myLoader.LoadShader();
    
    std::vector<Entity> entityList;    
    std::vector<Light> lights;
    
    Mesh cubeMesh = myLoader.LoadMesh("miku.stl");

    entityList.push_back( Entity(&cubeMesh) );
    entityList[0].getTransform()->setPosition(0.0f, -3.0f, 10.0f);

    glm::quat camRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 camPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    Camera myCamera = Camera(0.75f);
    myCamera.setPosition(&camPosition);
    myCamera.setRotation(&camRotation);

    lights.push_back(Light(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)));

    unsigned int VAO;
    myShader.use();

    for(int i = 0; i < lights.size(); i++ ){
	myShader.setVec3("u_Lights["+std::to_string(i)+"].position", lights[i].position);
	myShader.setVec3("u_Lights["+std::to_string(i)+"].color", lights[i].color);
    }

    while (!glfwWindowShouldClose(window))	{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float timeValue = glfwGetTime();

	myShader.setMat4("u_ViewProjectionMatrix", myCamera.viewMatrix() * myCamera.projectionMatrix());

	entityList[0].getTransform()->setRotation(1.55f, -timeValue, 0.0f);

	for(int i = 0; i < entityList.size(); i++){
	    myShader.setMat4("u_ModelMatrix", entityList[i].modelMatrix());
	    VAO = entityList[i].meshVAO();
	    glBindVertexArray(VAO);
	    glDrawElements(GL_TRIANGLES, entityList[i].vertexCount(), GL_UNSIGNED_INT, 0);
	}
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
