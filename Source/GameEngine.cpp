#include "GameEngine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void GameEngine::Update(float _deltaTime)
{

	lastFrameTime += _deltaTime;

	lightPos.x = glm::sin(lastFrameTime) * 2.0f;
	lightPos.z = glm::cos(lastFrameTime) * 2.0f;




}

void GameEngine::Render()
{

	/*Render Code Starts*/

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Try running the code by not clearing the Depth Buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// be sure to activate shader when setting uniforms/drawing objects
	coreShader->use();
	coreShader->setVec3("viewPos", this->camera->Position);

	// light properties
	glm::vec3 lightColor(1.f, 1.f, 1.f);
	//lightColor.x = sin(glfwGetTime() / 2.0f);
	//lightColor.y = sin(glfwGetTime() / 0.7f);
	//lightColor.z = sin(glfwGetTime() / 1.3f);
	glm::vec3 diffuseColor = lightColor   * glm::vec3(1.f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.4f); // low influence
	coreShader->setVec3("light.ambient", ambientColor);
	coreShader->setVec3("light.diffuse", diffuseColor);
	coreShader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	coreShader->setVec3("light.position", lightPos);

	// material properties
	coreShader->setVec3("material.ambient", selectedMaterial->ambient);
	coreShader->setVec3("material.diffuse", selectedMaterial->diffuse);
	coreShader->setVec3("material.specular", selectedMaterial->specular); // specular lighting doesn't have full effect on this object's material
	coreShader->setFloat("material.shininess", selectedMaterial->shininess);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800 / (float)600, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	coreShader->setMat4("projection", projection);
	coreShader->setMat4("view", view);

	// world transformation
	glm::mat4 model(1.0);
	coreShader->setMat4("model", model);

	// render the cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);


	// also draw the lamp object
	lightShader->use();
	lightShader->setMat4("projection", projection);
	lightShader->setMat4("view", view);
	model = glm::mat4(1.0);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	lightShader->setMat4("model", model);

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

GameEngine::GameEngine()
{
	coreShader = new Shader("./Source/lighting.vs", "./Source/lighting.frag");
	lightShader = new Shader("./Source/light.vs", "./Source/light.frag");

	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	for (unsigned int i = 0; i < 36; i++) {
		this->indices[i] = i;
	}

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

	// first, configure the cube's VAO (and VBO)
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	materials[0] = new Material("Emerald", glm::vec3(0.0215, 0.1745, 0.0215), glm::vec3(0.07568, 0.61424, 0.07568), glm::vec3(0.633, 0.727811, 0.633), 0.6);
	materials[1] = new Material("Jade", glm::vec3(0.135, 0.2225, 0.1575), glm::vec3(0.54, 0.89, 0.63), glm::vec3(0.316228, 0.316228, 0.316228), 0.1);
	materials[2] = new Material("Obsidian", glm::vec3(0.05375, 0.05, 0.06625), glm::vec3(0.18275, 0.17, 0.22525), glm::vec3(0.332741, 0.328634, 0.346435), 0.3);

	selectedMaterial = materials[0];

}


GameEngine::~GameEngine()
{
}
