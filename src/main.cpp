
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void)
{
    if (!glfwInit())	return -1;

    glfwSetErrorCallback(error_callback);


    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)	{
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window))	{	
        glClear(GL_COLOR_BUFFER_BIT);

	static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glReadBuffer(GL_COLOR, 0, red);
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
    if (key == GLFW_KEY_6 && action == GLFW_PRESS)
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}
