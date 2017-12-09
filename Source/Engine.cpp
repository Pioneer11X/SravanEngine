#include "Engine.h"
#include <iostream>
#include <assert.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Engine::Engine()
{

	// Init GLFW.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Sravan Engine", NULL, NULL);

	if (NULL == window) {
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		assert(NULL != window);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Check if glad is working with the Window.
	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	glViewport(0, 0, 400, 400);

}

int Engine::Run()
{

	while (!glfwWindowShouldClose(window))
	{
		// Process the Input.
		this->ProcessInput();

		/*Render Code Starts*/

		glClearColor(0.2, 0.2, .2, 1.);
		glClear(GL_COLOR_BUFFER_BIT);

		/*Render Code Ends*/

		// Swap the Buffers.
		glfwSwapBuffers(window);

		// Input to the Input Manager???
		glfwPollEvents();
	}

	return 0;
}

void Engine::ProcessInput()
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}

}


Engine::~Engine()
{
	glfwTerminate();
}
