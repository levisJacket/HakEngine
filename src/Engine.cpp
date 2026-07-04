#include "Engine.hpp"

static std::string PATH = "../PATHS.json";
void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool Engine::init(){   
    if (!glfwInit())	{
	std::cout << "Failed to initialize GLFW" << std::endl;
	return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "HakEngine", NULL, NULL);

    if (!window)	{
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))	{
	std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
	return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    
    entityManager = EntityManager();
    physicsManager = PhysicsManager(&entityManager);
    collisionManager = CollisionManager(&entityManager, &physicsManager);

    assetLoader = AssetLoader(PATH);
    shader = assetLoader.loadShader();
    renderer = Renderer(&entityManager, &shader);

    camera = Camera(0.75f);

    return true;
}

void Engine::run(){
    shader.use();

    glm::quat camRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 camPosition = glm::vec3(0.0f, 3.0f, 0.0f);
    camera.setPosition(&camPosition);
    camera.setRotation(&camRotation);
    //shader.setInt("u_Texture", 0);

    for(int i = 0; i < lights.size(); i++ ){
	shader.setVec3("u_Lights["+std::to_string(i)+"].position", lights[i].position);
	shader.setVec3("u_Lights["+std::to_string(i)+"].color", lights[i].color);
    }

    float timeValue = 0.0f, timeStep = 0.0f;
    while (!glfwWindowShouldClose(window))	{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	timeStep = glfwGetTime() - timeValue;
	timeValue = glfwGetTime();
	
	shader.setMat4("u_ViewProjectionMatrix", camera.viewMatrix() * camera.projectionMatrix());

	physicsManager.update(timeStep);
	collisionManager.resolve(timeStep);


	renderer.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::terminate(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::addLight(glm::vec3 position, glm::vec3 color){
    lights.push_back(Light(position, color));
}

unsigned int Engine::createEntity(std::string name){
    Mesh *mesh;
    int len = name.length();

    if (name.substr(len - 4) == ".stl"){
	Mesh *mesh = assetLoader.loadMesh(name);
	return entityManager.createEntity(mesh);
    } else if (name.substr(len - 4) == ".obj"){
	Mesh *mesh = assetLoader.loadMesh(name, name.substr(0, len - 4) + ".png");
	return entityManager.createEntity(mesh);
    } 
    return 0;
}

Entity* Engine::getEntity(unsigned int entityID){
    return entityManager.getEntity(entityID);
}

void Engine::addPhysics(unsigned int entityID, float mass){
    physicsManager.addPhysics(entityID, mass);
}

void Engine::addCollider(unsigned int entityID){
    collisionManager.addCollider(entityID);
}

void Engine::addImpulse(unsigned int entityID, glm::vec3 force){
    physicsManager.addImpulse(entityID, force);
}


Engine::Engine(){}

Engine::~Engine(){
    terminate();
}

void error_callback(int error, const char* description)	{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)	{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        
    if (key == GLFW_KEY_W && action == GLFW_PRESS){}
}
