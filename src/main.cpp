#include "AssetLoader.hpp"
#include "EntityManager.hpp"
#include "PhysicsManager.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Physics.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>

std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

static std::string PATH = "../PATHS.json";
void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

std::vector<Physics> physics;

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
    
    EntityManager entityManager = EntityManager();
    PhysicsManager physicsManager = PhysicsManager(&entityManager);
    Renderer renderer = Renderer(&entityManager, &myShader);

    std::vector<Light> lights;
    
    Mesh myMesh = myLoader.LoadMesh("sphere.stl");

    unsigned int ent1 = entityManager.createEntity(&myMesh);
    entityManager.getTransform(ent1)->setPosition(0.0f, 10.0f, 10.0f);
    
    lights.push_back(Light(glm::vec3(10.0, 5.0, 0.0), glm::vec3(0.5, 0.5, 0.5)));
    lights.push_back(Light(glm::vec3(-10.0, 0.0, 0.0), glm::vec3(0.5, 0.5, 0.5)));

    physicsManager.addPhysics(ent1);

    glm::quat camRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 camPosition = glm::vec3(0.0f, 5.0f, 0.0f);
    Camera myCamera = Camera(0.75f);
    myCamera.setPosition(&camPosition);
    myCamera.setRotation(&camRotation);

    unsigned int VAO;
    myShader.use();

    for(int i = 0; i < lights.size(); i++ ){
	myShader.setVec3("u_Lights["+std::to_string(i)+"].position", lights[i].position);
	myShader.setVec3("u_Lights["+std::to_string(i)+"].color", lights[i].color);
    }

    float timeValue = 0.0f, timeStep = 0.0f;
    while (!glfwWindowShouldClose(window))	{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	timeStep = glfwGetTime() - timeValue;
	timeValue = glfwGetTime();
	myShader.setMat4("u_ViewProjectionMatrix", myCamera.viewMatrix() * myCamera.projectionMatrix());

	physicsManager.update(timeStep);

	renderer.render();

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
        
    if (key == GLFW_KEY_W && action == GLFW_PRESS){}
}
