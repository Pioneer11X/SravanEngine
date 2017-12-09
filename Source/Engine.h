#pragma once

// Always include Glad before GLFW
#include <glad\glad.h>
#include <GLFW\glfw3.h>

class Engine
{
public:

	GLFWwindow * window;

	Engine();

	int Run();

	void ProcessInput();

	void Update();

	~Engine();
};

