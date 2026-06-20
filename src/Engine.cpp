#include "Engine.hpp"

bool Engine::init(){   
    if (!glfwInit())	{
	std::cout << "Failed to initialize GLFW" << std::endl;
	return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "HakEngine", NULL, NULL);

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

    AssetLoader assetLoader = AssetLoader(PATH);
    Shader shader = assetLoader.loadShader();
    
    EntityManager entityManager = EntityManager();
    PhysicsManager physicsManager = PhysicsManager(&entityManager);
    CollisionManager collisionManager = CollisionManager(&entityManager, &physicsManager);
    Renderer renderer = Renderer(&entityManager, &shader);
}

void Engine::run(){
    shader.use();

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

Engine::~Engine(){
    glfwDestroyWindow(window);
    glfwTerminate();
}
