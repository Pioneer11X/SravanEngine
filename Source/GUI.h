#pragma once

#include "GameEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <GLFW\glfw3.h>

class GUI
{

private:
	GUI();

public:

	bool show_test_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	GLFWwindow * window;

	GameEngine * engine;
	
	static GUI& getInstance() {
		static GUI instance;
		return instance;
	};

	void Run();

	void Render();

	~GUI();
};

