
#include "AssetLoader.hpp"
#include "EntityManager.hpp"
#include "PhysicsManager.hpp"
#include "CollisionManager.hpp"
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

class Engine {
private:
    EntityManager entityManager;
    PhysicsManager physicsManager;
    CollisionManager collisionManager;
    Renderer renderer;

    AssetLoader assetLoader;
    Shader shader;
    
    GLFWwindow* window;
public:
    Engine();     
    ~Engine();

    bool init();
    void run();
    void terminate();

    unsigned int createEntity();
};
