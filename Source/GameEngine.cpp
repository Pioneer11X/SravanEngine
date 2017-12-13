#include "GameEngine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void GameEngine::Update(float _deltaTime)
{

	lastFrameTime += _deltaTime;

	//lightPos.x = glm::sin(lastFrameTime) * 2.0f;
	//lightPos.z = glm::cos(lastFrameTime) * 2.0f;

}

void GameEngine::Render()
{

	/*Render Code Starts*/

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Try running the code by not clearing the Depth Buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// be sure to activate shader when setting uniforms/drawing objects
	//coreShader->use();
	//coreShader->setVec3("viewPos", this->camera->Position);

	/*pointLightingShader->use();
	pointLightingShader->setVec3("viewPos", this->camera->Position);*/

	spotLightingShader->use();

	// light properties
	glm::vec3 lightColor(1.f, 1.f, 1.f);
	//lightColor.x = sin(glfwGetTime() / 2.0f);
	//lightColor.y = sin(glfwGetTime() / 0.7f);
	//lightColor.z = sin(glfwGetTime() / 1.3f);
	glm::vec3 diffuseColor = lightColor   * glm::vec3(1.f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.4f); // low influence

	//coreShader->setVec3("light.ambient", ambientColor);
	//coreShader->setVec3("light.diffuse", diffuseColor);
	//coreShader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	//coreShader->setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

	//pointLightingShader->setVec3("light.position", lightPos);
	//pointLightingShader->setVec3("light.ambient", ambientColor);
	//pointLightingShader->setVec3("light.diffuse", diffuseColor);
	//pointLightingShader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	//pointLightingShader->setFloat("light.constant", 1.0f);
	//pointLightingShader->setFloat("light.linearConstant", 0.09f);
	//pointLightingShader->setFloat("light.quadraticConstant", 0.032f);

	spotLightingShader->setVec3("light.position", camera->Position);
	spotLightingShader->setVec3("light.direction", camera->Front);
	spotLightingShader->setFloat("light.cutoff", glm::cos(glm::radians(12.5f)));
	spotLightingShader->setVec3("light.ambient", ambientColor);
	spotLightingShader->setVec3("light.diffuse", diffuseColor);
	spotLightingShader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));


	// material properties
	//coreShader->setVec3("material.specular", selectedMaterial->specular); // specular lighting doesn't have full effect on this object's material
	//coreShader->setFloat("material.shininess", selectedMaterial->shininess);
	pointLightingShader->setVec3("material.specular", selectedMaterial->specular); // specular lighting doesn't have full effect on this object's material
	pointLightingShader->setFloat("material.shininess", selectedMaterial->shininess);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800 / (float)600, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	//coreShader->setMat4("projection", projection);
	//coreShader->setMat4("view", view);
	pointLightingShader->setMat4("projection", projection);
	pointLightingShader->setMat4("view", view);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	for (unsigned int i = 0; i < 10; i++) {
		glm::mat4 model(1.0);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		pointLightingShader->setMat4("model", model);

		// render the cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


	// also draw the lamp object
	lightShader->use();
	lightShader->setMat4("projection", projection);
	lightShader->setMat4("view", view);
	glm::mat4 model = glm::mat4(1.0);
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
	pointLightingShader = new Shader("./Source/pointLighting.vs", "./Source/pointLighting.frag");
	spotLightingShader = new Shader("./Source/spotLighting.vs", "./Source/spotLighting.frag");

	camera = new Camera(glm::vec3(0.0f, 1.5f, 3.0f));

	for (unsigned int i = 0; i < 36; i++) {
		this->indices[i] = i;
	}

	unsigned char * data = stbi_load("./Assets/Images/container2.png", &width, &height, &nrChannels, 0);

	assert(NULL != data);

	GLenum format;
	switch (nrChannels)
	{
	case 1:
		format = GL_RED;
	case 3:
		format = GL_RGB;
	case 4:
		format = GL_RGBA;
	default:
		format = GL_RGB;
		break;
	}
	format = GL_RGBA;

	glGenTextures(1, &texture1);
	
	glBindTexture(GL_TEXTURE_2D, texture1);

	// load and generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	data = stbi_load("./Assets/Images/container2_specular.png", &width, &height, &nrChannels, 0);
	assert(NULL != data);

	switch (nrChannels)
	{
	case 1:
		format = GL_RED;
	case 3:
		format = GL_RGB;
	case 4:
		format = GL_RGBA;
	default:
		format = GL_RGB;
		break;
	}
	format = GL_RGBA;

	glGenTextures(1, &texture2);

	glBindTexture(GL_TEXTURE_2D, texture2);

	// load and generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Texture Loading Stuff Ends */

	// first, configure the cube's VAO (and VBO)
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture Attribute.
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	materials[0] = new Material("Emerald", glm::vec3(0.0215, 0.1745, 0.0215), glm::vec3(0.07568, 0.61424, 0.07568), glm::vec3(0.633, 0.727811, 0.633), 0.6);
	materials[1] = new Material("Jade", glm::vec3(0.135, 0.2225, 0.1575), glm::vec3(0.54, 0.89, 0.63), glm::vec3(0.316228, 0.316228, 0.316228), 0.1);
	materials[2] = new Material("Obsidian", glm::vec3(0.05375, 0.05, 0.06625), glm::vec3(0.18275, 0.17, 0.22525), glm::vec3(0.332741, 0.328634, 0.346435), 0.3);
	materials[3] = new Material("Pearl", glm::vec3(0.25, 0.20725, 0.20725), glm::vec3(1.0, 0.829, 0.829), glm::vec3(0.296648, 0.296648, 0.296648), 0.088);
	materials[4] = new Material("Ruby", glm::vec3(0.1745, 0.01175, 0.01175), glm::vec3(0.61424, 0.04136, 0.04136), glm::vec3(0.727811, 0.626959, 0.626959), 0.6);
	materials[5] = new Material("Turquoise", glm::vec3(0.1, 0.18725, 0.1745), glm::vec3(0.396, 0.74151, 0.69102), glm::vec3(0.297254, 0.30829, 0.306678), 0.1);
	materials[6] = new Material("Brass", glm::vec3(0.329412, 0.223529, 0.027451), glm::vec3(0.780392, 0.568627, 0.113725), glm::vec3(0.992157, 0.941176, 0.807843), 0.21794872);


	selectedMaterial = materials[0];

	//coreShader->use();
	//coreShader->setInt("material.diffuse", 0);
	//coreShader->setInt("material.specular", 1);

	//pointLightingShader->use();
	//pointLightingShader->setInt("material.diffuse", 0);
	//pointLightingShader->setInt("material.specular", 1);

	spotLightingShader->use();
	spotLightingShader->setInt("material.diffuse", 0);
	spotLightingShader->setInt("material.specular", 1);

}


GameEngine::~GameEngine()
{
}
