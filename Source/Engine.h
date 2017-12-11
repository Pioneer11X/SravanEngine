#pragma once

// Always include Glad before GLFW
#include <glad\glad.h>
#include "GameEngine.h"

#include <memory>
#include "Gui.h"

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

	GameEngine * engine;

	int Run();

	void ProcessInput();

	void Update();

	~Engine();
};

