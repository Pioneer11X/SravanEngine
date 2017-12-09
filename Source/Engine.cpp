#include "Engine.h"
#include <iostream>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

	glViewport(0, 0, 800, 600);

	coreShader = new Shader("./Source/core.vs", "./Source/core.fs");

}

int Engine::Run()
{
	// Rectangle
	float vertices[] = {
		// positions         // colors			// Tex Coords.
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,	1.0f, 0.0f,			// bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f,			// bottom left
		0.5f,  0.5f, 0.0f,  0.5f, 0.5f, 1.0f,	1.0f, 1.0f,			// top right
		-0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f,	0.0f, 1.0f						// top left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	/* Texture Loading Stuff */

	int width, height, nrChannels;
	unsigned char * data = stbi_load("./Assets/Images/wall.jpg", &width, &height, &nrChannels, 0);

	assert(NULL != data);

	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);



	stbi_image_free(data);

	data = stbi_load("./Assets/Images/container.jpg", &width, &height, &nrChannels, 0);

	assert(NULL != data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// set the texture wrapping/filtering options (on the currently bound texture object)

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load and generate the texture

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	/* Texture Loading Stuff Ends */

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	coreShader->use();
	glUniform1i(glGetUniformLocation(this->coreShader->ID, "texture1"), 0);
	glUniform1i(glGetUniformLocation(this->coreShader->ID, "texture2"), 1);

	while (!glfwWindowShouldClose(window))
	{
		// Process the Input.
		this->ProcessInput();

		/*Render Code Starts*/

		glClearColor(0.2, 0.2, .2, 1.);
		glClear(GL_COLOR_BUFFER_BIT);

		// update the uniform color
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(this->coreShader->ID, "ourColour");
		glUniform4f(vertexColorLocation, 0.5f, greenValue, 0.5f, 1.0f);

		// Be careful when activating Shader. I messed up pretty bad.
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		coreShader->use();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// glUniform1i(glGetUniformLocation(this->coreShader->ID, "ourTexture"), 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

void Engine::Update()
{



}


Engine::~Engine()
{
	glfwTerminate();
}

