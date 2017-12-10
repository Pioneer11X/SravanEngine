#pragma once

// Always include Glad before GLFW
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Shader.h"
#include "Camera.h"
#include <memory>


class Engine
{
private:

	Engine();

public:

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

	Camera * camera;

	int Run();

	void ProcessInput();

	void Update();

	~Engine();
};

