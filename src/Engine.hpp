#pragma once

#include "AssetLoader.hpp"
#include "EntityManager.hpp"
#include "PhysicsManager.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

class Engine {
private:
    EntityManager entityManager;
    PhysicsManager physicsManager;
    AssetLoader assetLoader;

    Renderer renderer;
    Shader shader;
    std::vector<Light> lights;
    Camera camera;

    GLFWwindow* window;

    float timeValue = 0.0f; float timeStep = 0.0f;

public:
    Engine() : 
	entityManager(EntityManager()),
	physicsManager(PhysicsManager(&entityManager)) {};
    ~Engine();

    bool init();
    void run();
    void terminate();

    void rigCamera(glm::vec3 *position, glm::quat *rotation);
    void rigCamera(unsigned int entityID);
    void addLight(Light light);

    unsigned int createEntity(std::string name);
    Entity* getEntity(unsigned int entityID);
    std::function<void(int key, int action)> keyCallBack;
    std::function<void(int button, int action)> mouseButtonCallBack;

    void addBody(unsigned int entityID, BodyInfo info);
    void addImpulse(unsigned int entityID, glm::vec3 force);
};
