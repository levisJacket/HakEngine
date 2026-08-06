#include "Engine.hpp"

static std::string PATH = "../PATHS.json";
void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

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

    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))	{
	std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
	return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    physicsManager.init(); // Initialize Jolt Physics System!

    assetLoader = AssetLoader(PATH);
    shader = assetLoader.loadShader();
    renderer = Renderer(&entityManager, &shader);

    camera = Camera(0.75f);

    return true;
}

void Engine::run(){
    shader.use();

    for(int i = 0; i < lights.size(); i++ ){
	shader.setVec3("u_Lights["+std::to_string(i)+"].position", lights[i].position);
	shader.setVec3("u_Lights["+std::to_string(i)+"].color", lights[i].color);
	shader.setFloat("u_Lights["+std::to_string(i)+"].radius", lights[i].radius);
	shader.setFloat("u_Lights["+std::to_string(i)+"].intensity", lights[i].intensity);
    }

    timeValue = 0.0f; timeStep = 0.0f;
    while (!glfwWindowShouldClose(window))	{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	timeStep = glfwGetTime() - timeValue;
	timeValue += timeStep;

	physicsManager.update(timeStep);

	for(int i = 0; i < lights.size(); i++ ){
	    shader.setVec3("u_Lights["+std::to_string(i)+"].position", lights[i].position);
	    shader.setVec3("u_Lights["+std::to_string(i)+"].color", lights[i].color);
	    shader.setFloat("u_Lights["+std::to_string(i)+"].radius", lights[i].radius);
	    shader.setFloat("u_Lights["+std::to_string(i)+"].intensity", lights[i].intensity);
	}
	
	shader.setMat4("u_ViewProjectionMatrix", camera.viewProjectionMatrix());
	renderer.render();
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

void Engine::terminate(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::rigCamera(glm::vec3 *position, glm::quat *rotation){
    camera.setPosition(position);
    camera.setRotation(rotation);
}

void Engine::rigCamera(unsigned int entityID){
    Entity *entity = getEntity(entityID);
    Transform *t = entity->getTransform();

    camera.setPosition(&t->position);
    camera.setRotation(&t->rotation);
}

void Engine::addLight(Light light){
    lights.push_back(light);
}

unsigned int Engine::createEntity(std::string name){
    Mesh *mesh;
    int len = name.length();
    unsigned int entityID = 0;

    if (name.substr(len - 4) == ".stl"){
	Mesh *mesh = assetLoader.loadMesh(name);
	entityID = entityManager.createEntity(mesh);
    } else if (name.substr(len - 4) == ".obj"){
	Mesh *mesh = assetLoader.loadMesh(name, name.substr(0, len - 4) + ".png");
	entityID = entityManager.createEntity(mesh);
    } 

    return entityID;
}

Entity* Engine::getEntity(unsigned int entityID){
    return entityManager.getEntity(entityID);
}

void Engine::addBody(unsigned int entityID, BodyInfo info){
    physicsManager.addBody(entityID, info);
}

void Engine::addImpulse(unsigned int entityID, glm::vec3 force){
    physicsManager.addImpulse(entityID, force);
}

Engine::~Engine(){
    terminate();
}

void error_callback(int error, const char* description)	{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    engine->keyCallBack(key, action);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
}
