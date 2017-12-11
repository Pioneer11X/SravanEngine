#pragma once

// Always include Glad before GLFW
#include <glad\glad.h>

#include "Shader.h"
#include "Camera.h"
#include <memory>
#include "Gui.h"

class Engine
{
private:

	Engine();

public:

	glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 toyColour = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 result = lightColour * toyColour;

	static Engine& getInstance() {
		static Engine instance;
		return instance;
	};

	// Timing Variables.
	float deltaTime = 0.0f;
	float lastFrameTime = 0.0f;
	float currentFrameTime = 0.0f;

	// Mouse Input Variables.
	bool firstInput = true;
	float lastX = 400, lastY = 300; // Set them to center.
	float sensitivity = 0.05f;

	GLFWwindow * window;

	Shader * coreShader;
	Shader * lightShader;

	Camera * camera;

	int Run();

	void ProcessInput();

	void Update();

	~Engine();
};

