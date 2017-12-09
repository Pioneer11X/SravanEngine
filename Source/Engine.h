#pragma once

// Always include Glad before GLFW
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Shader.h"

#include <memory>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Engine
{
public:

	GLFWwindow * window;

	Shader * coreShader;

	Engine();

	int Run();

	void ProcessInput();

	void Update();

	~Engine();
};

