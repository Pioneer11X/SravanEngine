#include "GUI.h"
#include <stdio.h>

GUI::GUI()
{
}


void GUI::Run()
{

	ImGui_ImplGlfwGL3_Init(window, true);

	ImGui_ImplGlfwGL3_NewFrame();

	// 1. Show a simple window.
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug".
	{

		if (ImGui::BeginMainMenuBar()) {

			if (ImGui::BeginMenu("Materials")) {
				if (ImGui::MenuItem("Emerald")) {
					printf("Emerald Selected\n");
				};
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		static float f = 0.0f;
		ImGui::Text("Hello, world!");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);
		if (ImGui::Button("Test Window")) show_test_window ^= 1;
		if (ImGui::Button("Another Window")) show_another_window ^= 1;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		ImGui::End();
	}

	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow().
	if (show_test_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

void GUI::Render()
{
	ImGui::Render();
}

GUI::~GUI()
{
}
