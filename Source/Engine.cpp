#include "Engine.h"
#include <iostream>
#include <vector>
#include <assert.h>



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

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

	GUI::getInstance().window = window;

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Check if glad is working with the Window.
	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	glViewport(0, 0, 800, 600);

	engine = new GameEngine();

	GUI::getInstance().engine = engine;

}

int Engine::Run()
{
	

	while (!glfwWindowShouldClose(window))
	{

		/*Timed Update Stuff*/

		currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		engine->Update(deltaTime);
	
		/*Timed Update Stuff ends*/

		// Process the Input.
		this->ProcessInput();

		GUI::getInstance().Run();

		engine->Render();

		GUI::getInstance().Render();

		/*Render Code Ends*/

		// Swap the Buffers.
		glfwSwapBuffers(window);

		assert(GL_NO_ERROR == glGetError());

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

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		engine->camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		engine->camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		engine->camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		engine->camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

}

void Engine::Update()
{



}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{


	if (Engine::getInstance().firstInput)
	{
		Engine::getInstance().lastX = xpos;
		Engine::getInstance().lastY = ypos;
		Engine::getInstance().firstInput = false;
	}

	float xoffset = xpos - Engine::getInstance().lastX;
	float yoffset = Engine::getInstance().lastY - ypos; // reversed since y-coordinates go from bottom to top

	Engine::getInstance().lastX = xpos;
	Engine::getInstance().lastY = ypos;

	Engine::getInstance().engine->camera->ProcessMouseMovement(xoffset, yoffset, true);

	// std::cout << xpos << " , " << ypos << std::endl;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Engine::getInstance().engine->camera->ProcessMouseScroll(yoffset);
}


Engine::~Engine()
{
	glfwTerminate();
}
