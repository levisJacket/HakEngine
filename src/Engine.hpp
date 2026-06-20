
#include "AssetLoader.hpp"
#include "EntityManager.hpp"
#include "PhysicsManager.hpp"
#include "CollisionManager.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>

class Engine {
private:
    EntityManager entityManager;
    PhysicsManager physicsManager;
    CollisionManager collisionManager;
    Renderer renderer;

    AssetLoader assetLoader;
    Shader shader;
    
    std::vector<Light> lights;
    GLFWwindow* window;
    Camera camera;
public:
    Engine();     
    ~Engine();

    bool init();
    void run();
    void terminate();

    void addLight(glm::vec3 position, glm::vec3 color);

    unsigned int createEntity(std::string name);
    Entity* getEntity(unsigned int entityID);
    void addPhysics(unsigned int entityID, float mass);
    void addCollider(unsigned int entityID);

    void addImpulse(unsigned int entityID, glm::vec3 force);
};
