#include "SkyRoads.h"
#include "Objects/SimpleCube.h"
#include "Objects/Heart.h"

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <Core/Engine.h>

using namespace std;

float minSpeedZ = 5.0f;
float maxSpeedZ = 20.0f;
float speedZ = 0.0f;
float previousSpeedZ = 0.0f;
float previousAspect = 0.0f;
float previousRotateSpeed = 0.0f;

float speedPlatformDuration = 0.0f;
float platformMaxSpeedZ = 30.0f;

float speedX = 1.75f;
float speedY = 0.0f;

float maxRotateSpeedX = 0.80f;
float minRotateSpeedX = 0.1f;
float rotateSpeedX = 0.1f;
float rotateX = 0;

float accY = -0.001f;
float gravity = -9.81f * 1.85f;

float platformScaleX = 0.25f;
float platformScaleY = 0.1f;

int maxPlatformScaleZ = 30;
int minPlatformScaleZ = 5;

int maxHelperScaleZ = 10;
int minHelperScaleZ = 3;

int minSpacing = 3;
int maxSpacing = 8;

float helperPlatformOffset = 0.5f;
float distanceForBackup = -40.0f;

glm::vec3 camPos;
glm::vec3 initCamPos;

vector<SkyRoads::Platform> platforms;
vector<SkyRoads::Platform> helperPlatform;
vector<int> removePlatforms;
vector<glm::vec3> livesPosition;
SkyRoads::Player player;

float aspectX = 60.0f;
float minAspectX = 60.0f;
float maxAspectX = 70.0f;

bool firstPerson = false;

bool reverseValues = true;

float maxFuel = 100;
float fuel = 100;

int speedPlatformChance = 25;
int fuelPlatformChance = 15;
int fuelLossPlatformChance = 20;
int deathPlatformChance = 10;
int lifePlatformChance = 5;

int speedPlatformCD = 7;
int fuelPlatformCD = 10;
int fuelLossPlatformCD = 7;
int deathPlatformCD = 10;
int lifePlatformCD = 20;

int curSpeedPlatformCD = 0;
int curFuelPlatformCD = 0;
int curFuelLossPlatformCD = 0;
int curDeathPlatformCD = 0;
int curLifePlatformCD = 0;

int livesRemaining = 3;
bool freshReset = false;

SkyRoads::SkyRoads()
{
}

SkyRoads::~SkyRoads()
{
}

void SkyRoads::Init()
{
	// Initialise randomness
	srand(time(NULL));

	// Set camera
	glm::ivec2 resolution = window->GetResolution();
	camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 1.5f, 3));
	camPos = glm::vec3(0, 1.5f, 3);	
	initCamPos = glm::vec3(0, 1.5f, 3);

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

		mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;

		mesh = new Mesh("blenderSphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "BlendSphere3.obj");
		meshes[mesh->GetMeshID()] = mesh;

		mesh = SimpleCube::CreateCube("LeCube");
		AddMeshToList(mesh);
		mesh = SimpleCube::CreateActiveCube("LeActiveCube");
		AddMeshToList(mesh);
		mesh = SimpleCube::CreateSpeedCube("LeSpeedCube");
		AddMeshToList(mesh);
		mesh = SimpleCube::CreateFuelBar("LeFuelCubeBar");
		AddMeshToList(mesh);
		mesh = SimpleCube::CreateFuelBackgroundBar("LeFuelBackgroundCube");
		AddMeshToList(mesh);
		mesh = Heart::CreateHeart("LeHeart");
		AddMeshToList(mesh);
		mesh = SimpleCube::CreateFuelPlatform("LeFuelCube");
		AddMeshToList(mesh);
		mesh = SimpleCube::CreateFuelLossPlatform("LeFuelLossCube");
		AddMeshToList(mesh);
		mesh = SimpleCube::CreateDeathPlatform("LeDeathCube");
		AddMeshToList(mesh);
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderSkyRoads");
		shader->AddShader("Source/Laboratoare/Tema1Master/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema1Master/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("Player");
		shader->AddShader("Source/Laboratoare/Tema1Master/Shaders/PlayerVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema1Master/Shaders/PlayerFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("LifePlatform");
		shader->AddShader("Source/Laboratoare/Tema1Master/Shaders/HealthPlatformVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema1Master/Shaders/HealthPlatformFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("UI");
		shader->AddShader("Source/Laboratoare/Tema1Master/Shaders/UIVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema1Master/Shaders/UIFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("UITest");
		shader->AddShader("Source/Laboratoare/Tema1Master/Shaders/UIVerTest.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema1Master/Shaders/UIFrTest.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Compute initial position of dummy platforms
	float cc = -1;

	for (int i = 0; i < 3; ++i) {
		Platform currentPlatform;
		currentPlatform.maxX *= platformScaleX;
		currentPlatform.minX *= platformScaleX;
		currentPlatform.maxY *= platformScaleY;
		currentPlatform.minY *= platformScaleY;
		currentPlatform.maxZ *= 10.0f;
		currentPlatform.minZ *= 10.0f;

		currentPlatform.maxX += cc;
		currentPlatform.minX += cc;
		currentPlatform.minY -= 0.1f;
		currentPlatform.maxY -= 0.1f;

		currentPlatform.centerX += cc;
		currentPlatform.centerY -= 0.1f;

		currentPlatform.laneOffset = cc;

		currentPlatform.scaleZ = 10;

		currentPlatform.lane = i * 2;

		cc++;

		printf("The current limits are: x: (%.2f %.2f), y(%.2f, %.2f), z(%.2f, %.2f) for platform %d\n", 
			currentPlatform.minX,
			currentPlatform.maxX,
			currentPlatform.minY,
			currentPlatform.maxY,
			currentPlatform.minZ,
			currentPlatform.maxZ,
			i);

		platforms.push_back(currentPlatform);
	}

	// Add lives position
	livesPosition.push_back(glm::vec3(0.6f, 0.75, 0));
	livesPosition.push_back(glm::vec3(0.7f, 0.75, 0));
	livesPosition.push_back(glm::vec3(0.8f, 0.75, 0));
}

Mesh* SkyRoads::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}


void SkyRoads::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void SkyRoads::Update(float deltaTimeSeconds)
{
	if (player.isDead) {
		RenderDeathCam(deltaTimeSeconds);
		return;
	}

	// End condition
	if (player.posY < -7) {
		if (livesRemaining <= 0)
			player.isDead = true;
		else {
			livesRemaining--;
			ResetPlayerPosition();
		}
	}

	/*glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.3, 1));
	RenderSimpleMesh(meshes["LeFuelCubeBar"], shaders["UITest"], modelMatrix);*/

	RenderHearts();
	RenderFuelBar();
	SetCameraPerspective();

	// Manage buffs
	ManageSpeedBuff(deltaTimeSeconds);
	
	bool abovePlatform = false;
	int index = -1;

	// Check if player is on platforms
	index = CheckPlayerAbovePlatformXZ();
	if (index != -1) {
		abovePlatform = true;
	}

	// If the player is going to go through the platform, don't let him
	// Place him on top of the landing platform
	if (abovePlatform) {
		if (player.posY + deltaTimeSeconds * accY < platforms[index].maxY && player.posY + deltaTimeSeconds * accY >= platforms[index].maxY - 0.1f) {
			player.posY = platforms[index].maxY;
			player.airborne = false;
			platforms[index].isPlayerAbove = true;

			if (!platforms[index].appliedEffect) {
				ApplyPlatformEffect(index);
			}
			
			accY = -0.001f;
		}
		else if (player.posY > platforms[index].maxY) {
			platforms[index].isPlayerAbove = false;
		}
	}
	else {
		player.airborne = true;
	}

	// Update the rotation of the ball
	rotateX -= rotateSpeedX;
	if (rotateX < -360) {
		rotateX = 0;
	}

	// Apply gravity only when the player is in the air
	if (!freshReset && player.airborne) {
		accY += deltaTimeSeconds * gravity;
		if (accY > 0) {
			fuel -= deltaTimeSeconds * 5;
		}
	}

	// Limit the maximum speed on Y
	if (accY < -10) {
		accY = -10;
	}

	// Update the player position on Y
	player.posY += deltaTimeSeconds * accY;

	// Move all platforms
	MovePlatforms(deltaTimeSeconds);

	// Remove the platforms that would dissapear
	RemovePlatforms();

	// Render objects
	RenderPlatforms();
	RenderPlayer(glm::vec3(1, 0, 0));
}

void SkyRoads::SetCameraPerspective()
{
	camera->SetPerspective(aspectX, window->props.aspectRatio, 0.01f, 400.0f);
	if (firstPerson) {
		camera->SetPosition(glm::vec3(player.posX, player.posY + 0.130 + 0.17, player.posZ - 0.3f));
		camPos = glm::vec3(player.posX, player.posY + 0.130 + 0.17, player.posZ - 0.3f);
	}
	else {
		camera->SetPosition(initCamPos);
		camPos = initCamPos;
	}
}

void SkyRoads::RenderFuelBar()
{
	float percent = (float)fuel / maxFuel;
	if (percent < 0) {
		percent = 0;
	}

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.7, 0.62, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.20f, 0.07f, 0.01f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3((percent - 1), 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(percent, 1, 1));
	RenderSimpleMesh(meshes["LeFuelCubeBar"], shaders["UITest"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.7, 0.62, 0.05));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.20f, 0.07f, 0.01f));
	RenderSimpleMesh(meshes["LeFuelBackgroundCube"], shaders["UITest"], modelMatrix);

	// Render the fuel bar
	if (speedPlatformDuration > 0) {
		percent = speedPlatformDuration / 5.0f;

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.7, 0.3, 0.05));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.20f, 0.07f, 0.01f));
		modelMatrix = glm::translate(modelMatrix, glm::vec3((percent - 1), 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(percent, 1, 1));
		RenderSimpleMesh(meshes["LeSpeedCube"], shaders["UITest"], modelMatrix);
	}
}

void SkyRoads::RenderDeathCam(float deltaTimeSeconds)
{
	// Render the ball
	RenderPlayer(glm::vec3(1, 1, 1));

	// Keep spinning it
	rotateX -= rotateSpeedX;
	if (rotateX < -360) {
		rotateX = 0;
	}

	if (abs(camPos.x - player.posX) > 0.02f) {
		if (camPos.x - player.posX > 0) {
			camPos.x -= deltaTimeSeconds * 3;
		}
		else {
			camPos.x += deltaTimeSeconds * 3;
		}

	}

	if (abs(camPos.y - (player.posY + 0.13)) > 0.02f) {
		if (camPos.y - player.posY > 0) {
			camPos.y -= deltaTimeSeconds * 3;
		}
		else {
			camPos.y += deltaTimeSeconds * 3;
		}
	}

	if (abs(camPos.z - player.posZ) > .5f) {
		if (camPos.z - player.posZ > 0) {
			camPos.z -= deltaTimeSeconds * 3;
		}
		else {
			camPos.z += deltaTimeSeconds * 3;
		}
	}

	camera->SetPosition(camPos);
}

void SkyRoads::FrameEnd()
{
	//DrawCoordinatSystem();
}

void SkyRoads::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	// TODO : set shader uniform "Model" to modelMatrix
	int location = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));


	// TODO : get shader location for uniform mat4 "View"
	// TODO : set shader uniform "View" to viewMatrix
	location = glGetUniformLocation(shader->program, "View");
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();

	if (player.isDead) {
		glm::vec3 playerPos(player.posX, player.posY + 0.13, player.posZ);

		glm::vec3 dir = glm::normalize(camPos - playerPos);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, dir));
		glm::vec3 cameraUp = glm::cross(dir, cameraRight);

		viewMatrix = glm::lookAt(camPos, playerPos, cameraUp);
	}

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	// TODO : set shader uniform "Projection" to projectionMatrix
	location = glGetUniformLocation(shader->program, "Projection");
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Send the current time elapsed to the shader
	location = glGetUniformLocation(shader->program, "time");
	glUniform1f(location, Engine::GetElapsedTime());

	location = glGetUniformLocation(shader->program, "speedBuffDuration");
	glUniform1f(location, speedPlatformDuration);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void SkyRoads::OnInputUpdate(float deltaTime, int mods)
{
	if (!player.isDead) {
		if (window->KeyHold(GLFW_KEY_W) && speedPlatformDuration <= 0) {

			if (speedZ + deltaTime * 8 < maxSpeedZ) {
				speedZ += deltaTime * 8;
			}
			else {
				speedZ = maxSpeedZ;
			}

			if (aspectX + deltaTime * 2 < maxAspectX) {
				aspectX += deltaTime * 2;
			}
			else {
				aspectX = maxAspectX;
			}

			if (rotateSpeedX + deltaTime / 8 < maxRotateSpeedX) {
				rotateSpeedX += deltaTime / 8;
			}
			else {
				rotateSpeedX = maxRotateSpeedX;
			}

			if (speedZ < minSpeedZ) {
				speedZ = minSpeedZ;
			}

		}

		if (window->KeyHold(GLFW_KEY_S) && speedPlatformDuration <= 0) {
			if (speedZ - deltaTime * 8 > minSpeedZ) {
				speedZ -= deltaTime * 8;
			}
			else {
				speedZ = minSpeedZ;
			}

			if (aspectX - deltaTime * 2 > minAspectX) {
				aspectX -= deltaTime * 2;
			}
			else {
				aspectX = minAspectX;
			}

			if (rotateSpeedX - deltaTime / 8 > minRotateSpeedX) {
				rotateSpeedX -= deltaTime / 8;
			}
			else {
				rotateSpeedX = minRotateSpeedX;
			}
		}

		if (window->KeyHold(GLFW_KEY_A) && fuel > 0) {
			bool hitWall = false;

			// If it ever happens that there are NO platforms, move freely
			if (platforms.size() == 0) {
				player.posX -= deltaTime * speedX;
				return;
			}

			if (player.airborne) {
				for (int i = 0; i < platforms.size(); ++i) {
					if (player.posX - deltaTime * speedX <= platforms[i].maxX && player.posX - deltaTime * speedX >= platforms[i].minX) {
						if (player.posZ >= platforms[i].minZ && player.posZ <= platforms[i].maxZ) {
							if (player.posY < platforms[i].maxY - 0.05f && player.posY >= platforms[i].minY) {
								printf("Hitting right side of platftorm!\n");
								hitWall = true;
								break;
							}
						}
					}
				}

				if (!hitWall) {
					if (!freshReset)
						fuel -= deltaTime * 5;
					player.posX -= deltaTime * speedX;
				}

			}
			else {
				if (!freshReset)
					fuel -= deltaTime * 5;
				player.posX -= deltaTime * speedX;
			}

		}

		if (window->KeyHold(GLFW_KEY_D) && fuel > 0) {
			bool hitWall = false;

			if (platforms.size() == 0) {
				player.posX += deltaTime * speedX;
				return;
			}

			if (player.airborne) {
				for (int i = 0; i < platforms.size(); ++i) {
					if (player.posX + deltaTime * speedX >= platforms[i].minX && player.posX + deltaTime * speedX <= platforms[i].maxX) {
						if (player.posZ >= platforms[i].minZ && player.posZ <= platforms[i].maxZ) {
							if (player.posY < platforms[i].maxY - 0.05f && player.posY >= platforms[i].minY) {
								printf("Hitting right side of platftorm!\n");
								hitWall = true;
								break;
							}
						}
					}
				}

				if (!hitWall) {
					if (!freshReset)
						fuel -= deltaTime * 5;
					player.posX += deltaTime * speedX;
				}
			}
			else {
				if (!freshReset)
					fuel -= deltaTime * 5;
				player.posX += deltaTime * speedX;
			}
		}
	}
}

void SkyRoads::OnKeyPress(int key, int mods)
{
	if (window->KeyHold(GLFW_KEY_SPACE) ) {
		if (!freshReset) {
			if (fuel > 0) {
				std::cout << boolalpha;
				std::cout << "Airborne status: " << player.airborne << endl;

				if (!player.airborne) {
					accY = 5;
					player.airborne = true;
				}
			}
		}
		else {
			player.airborne = true;
			
			freshReset = false;
		}
	}

	if (window->KeyHold(GLFW_KEY_R)) {
		player.posX = 0;
		player.posY = 2;
		accY = 0;
		player.isDead = false;
	}

	if (window->KeyHold(GLFW_KEY_C)) {
		if (firstPerson) {
			firstPerson = false;
		}
		else {
			firstPerson = true;
		}
	}
}

void SkyRoads::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void SkyRoads::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void SkyRoads::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void SkyRoads::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void SkyRoads::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void SkyRoads::OnWindowResize(int width, int height)
{
}

void SkyRoads::GenerateNewPlatforms(Platform platform)
{
	Platform currentPlatform = SetPlatformLimits(platform, false, platform.laneOffset);

	//DebugPlatformInfo(currentPlatform, "current");

	// Position the platform accordingly
	float difference = platform.minZ - currentPlatform.maxZ - 0.02f;

	currentPlatform.minZ += difference;
	currentPlatform.maxZ += difference;
	currentPlatform.centerZ += difference;

	//DebugPlatformInfo(platform, "original");
	//DebugPlatformInfo(currentPlatform, "final");


	// Add some spacing between platforms at random
	int spacing = rand() % 2;

	if (spacing == 1) {
		float amount = (float)(rand() % ((maxSpacing - minSpacing) * maxSpacing)) / (maxSpacing * 1.0f) + minSpacing;
		currentPlatform.minZ -= amount;
		currentPlatform.maxZ -= amount;
		currentPlatform.centerZ -= amount;
	}

	currentPlatform.effect = SetPlatformEffect();

	//Decrease cooldowns
	curSpeedPlatformCD--;
	curFuelLossPlatformCD--;
	curFuelPlatformCD--;
	curDeathPlatformCD--;
	curLifePlatformCD--;

	platforms.push_back(currentPlatform);

	// Add helper platforms at random
	int helper = rand() % 2;

	if (helper == 1) {
		GenerateHelperPlatform(currentPlatform);
	}

}

void SkyRoads::GenerateHelperPlatform(Platform parent)
{
	//printf("Generating helper platform!\n");
	float dirOffset;

	if (parent.laneOffset == 0) {
		int random = rand() % 2;
		if (random == 0) {
			dirOffset = -0.5f;
		}
		else {
			dirOffset = 0.5f;
		}
	}
	else if (parent.laneOffset == -1) {
		dirOffset = 0.5f;
	}
	else {
		dirOffset = -0.5f;
	}

	Platform helper = SetPlatformLimits(parent, true, parent.laneOffset + dirOffset);

	helper.isHelper = true;
	helper.lane = parent.lane + (int)dirOffset * 2;

	// Spawn the helper to the center of the new platform
	helper.minZ += parent.centerZ;
	helper.maxZ += parent.centerZ;
	helper.centerZ = parent.centerZ;

	//DebugPlatformInfo(helper, "final HELPER");

	platforms.push_back(helper);
}

SkyRoads::Platform SkyRoads::SetPlatformLimits(Platform platform, bool helper, float offset)
{
	Platform curPlat;

	if (!helper) {
		curPlat.scaleZ = (float)(rand() % ((maxPlatformScaleZ - minPlatformScaleZ) * maxPlatformScaleZ)) / (maxPlatformScaleZ * 1.0f) + minPlatformScaleZ;
	}
	else {
		curPlat.scaleZ = (float)(rand() % ((maxHelperScaleZ - minHelperScaleZ) * maxHelperScaleZ)) / (maxHelperScaleZ * 1.0f) + minHelperScaleZ;
	}

	curPlat.maxX *= platformScaleX;
	curPlat.minX *= platformScaleX;
	curPlat.maxY *= platformScaleY;
	curPlat.minY *= platformScaleY;
	curPlat.maxZ *= curPlat.scaleZ;
	curPlat.minZ *= curPlat.scaleZ;

	curPlat.maxX += offset;
	curPlat.minX += offset;
	curPlat.minY -= 0.1f;
	curPlat.maxY -= 0.1f;

	curPlat.centerX += offset;
	curPlat.centerY -= 0.1f;

	curPlat.laneOffset = offset;
	curPlat.lane = platform.lane; // TODO: this is different for helper platforms

	return curPlat;
}

void SkyRoads::RenderPlatforms()
{
	for (int i = 0; i < platforms.size(); ++i) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(platforms[i].centerX, platforms[i].centerY, platforms[i].centerZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(platformScaleX, platformScaleY, platforms[i].scaleZ));

		if (platforms[i].isPlayerAbove) {
			RenderSimpleMesh(meshes["LeActiveCube"], shaders["ShaderSkyRoads"], modelMatrix);
		}
		else if (platforms[i].effect == 1) {
			RenderSimpleMesh(meshes["LeSpeedCube"], shaders["ShaderSkyRoads"], modelMatrix);
		}
		
		else if (platforms[i].effect == 2) {
			RenderSimpleMesh(meshes["LeFuelLossCube"], shaders["ShaderSkyRoads"], modelMatrix);
		}
		else if (platforms[i].effect == 3) {
			RenderSimpleMesh(meshes["LeFuelCube"], shaders["ShaderSkyRoads"], modelMatrix);
		}
		else if (platforms[i].effect == 4) {
			RenderSimpleMesh(meshes["LeDeathCube"], shaders["ShaderSkyRoads"], modelMatrix);
		}
		else if (platforms[i].effect == 5) {
			RenderSimpleMesh(meshes["LeCube"], shaders["LifePlatform"], modelMatrix);

		}
		else {
			RenderSimpleMesh(meshes["LeCube"], shaders["ShaderSkyRoads"], modelMatrix);
		}
	}
}

void SkyRoads::MovePlatforms(float deltaTime)
{
	removePlatforms.clear();

	for (int i = 0; i < platforms.size(); ++i) {
		platforms[i].minZ += deltaTime * speedZ;
		platforms[i].maxZ += deltaTime * speedZ;
		platforms[i].centerZ += deltaTime * speedZ;

		// When the platform is coming close enough to the player, generate a new one
		if (platforms[i].minZ > distanceForBackup && !platforms[i].createdBackup && !platforms[i].isHelper) {
			platforms[i].createdBackup = true;
			GenerateNewPlatforms(platforms[i]);
		}

		// When the platform goes completely off screen, mark it for deletion
		if (platforms[i].minZ > 5) {
			removePlatforms.push_back(i);
		}
	}
}

void SkyRoads::RemovePlatforms()
{
	int err = 0;
	for (int i = 0; i < removePlatforms.size(); ++i) {
		int index = removePlatforms[i] - err;
		platforms.erase(platforms.begin() + index);
		err++;
		//printf("The number of platforms remaining: %ld!\n", platforms.size());
	}
}

void SkyRoads::RenderPlayer(glm::vec3 axis)
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(player.posX, player.posY, player.posZ));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.130f, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 0.25f, 0.25f));
	modelMatrix = glm::rotate(modelMatrix, rotateX, axis);
	RenderSimpleMesh(meshes["sphere"], shaders["Player"], modelMatrix);
}

void SkyRoads::RenderHearts()
{
	for (int i = 0; i < livesRemaining; ++i) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, livesPosition[i]);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
		RenderSimpleMesh(meshes["LeHeart"], shaders["UITest"], modelMatrix);
	}
}

void SkyRoads::ManageSpeedBuff(float deltaTime)
{
	if (speedPlatformDuration > 0) {
		speedPlatformDuration -= deltaTime;

		if (aspectX < 90) {
			aspectX += deltaTime * 100; // TODO: do this over a period of a few seconds
		}

		if (rotateSpeedX < 1.0f) {
			rotateSpeedX += deltaTime * 2;
		}

	}
	else if (!reverseValues) {
		reverseValues = true;
		speedZ = previousSpeedZ;
		aspectX = previousAspect;
		rotateSpeedX = previousRotateSpeed;
	}
}

int SkyRoads::CheckPlayerAbovePlatformXZ()
{
	bool abovePlatform = false;
	int index = -1;

	for (int i = 0; i < platforms.size(); ++i) {
		if (abovePlatform) {
			platforms[i].isPlayerAbove = false;
		}
		else {
			if (player.posX >= platforms[i].minX && player.posX <= platforms[i].maxX) {
				if (player.posZ >= platforms[i].minZ && player.posZ <= platforms[i].maxZ) {
					abovePlatform = true;
					index = i;
				}
				else
					platforms[i].isPlayerAbove = false;
			}
			else {
				platforms[i].isPlayerAbove = false;
			}
		}
	}

	return index;
}

void SkyRoads::ApplyPlatformEffect(int index)
{
	platforms[index].appliedEffect = true;

	if (platforms[index].effect == 1 && speedPlatformDuration <= 0) {
		previousSpeedZ = speedZ;
		previousAspect = aspectX;
		previousRotateSpeed = rotateSpeedX;
		reverseValues = false;

		speedZ = platformMaxSpeedZ;
		speedPlatformDuration = 5.0f;
	}
	else if (platforms[index].effect == 1 && speedPlatformDuration > 0) {
		speedPlatformDuration = 5.0f;
	}
	else if (platforms[index].effect == 2) {
		fuel -= maxFuel / 10;
		if (fuel <= 0) {
			fuel = 0;
		}
	}
	else if (platforms[index].effect == 3) { //TODO: KEEP CHANGING THIS AS MORE PLATFORM TYPES ARE ADDED
		fuel += maxFuel / 3;
		if (fuel > maxFuel) {
			fuel = maxFuel;
		}
	}
	else if (platforms[index].effect == 4) { //TODO: KEEP CHANGING THIS AS MORE PLATFORM TYPES ARE ADDED
		livesRemaining--;
		ResetPlayerPosition();
	}
	else if (platforms[index].effect == 5) {
		livesRemaining++;
	}
}

void SkyRoads::DebugPlatformInfo(Platform curPlat, char* specifier)
{
	printf("The %s limits are: x: (%.2f %.2f), y(%.2f, %.2f), z(%.2f, %.2f) and centerZ: %.2f\n",
		specifier,
		curPlat.minX,
		curPlat.maxX,
		curPlat.minY,
		curPlat.maxY,
		curPlat.minZ,
		curPlat.maxZ,
		curPlat.centerZ);
}

void SkyRoads::ResetPlayerPosition()
{
	player.posX = 0;
	player.posY = 2;
	accY = 0;
	freshReset = true;
	
	if (fuel < maxFuel / 3)
		fuel = maxFuel / 3;
}

int SkyRoads::SetPlatformEffect()
{
	int chance;
	int effect = 0;
	bool setEffect = false;
	if (curSpeedPlatformCD <= 0) {
		chance = rand() % 100;
		if (chance < speedPlatformChance) {
			curSpeedPlatformCD = speedPlatformCD;
			effect = 1;
			setEffect = true;
		}
	}

	if (curFuelLossPlatformCD <= 0 && !setEffect) {
		chance = rand() % 100;
		if (chance < fuelLossPlatformChance) {
			curFuelLossPlatformCD = fuelLossPlatformCD;
			effect = 2;
			setEffect = true;
		}
	}

	if (curFuelPlatformCD <= 0 && !setEffect) {
		printf("Rolling for FUEL!\n");
		chance = rand() % 100;
		if (chance < fuelPlatformChance) {
			curFuelPlatformCD = fuelPlatformCD;
			effect = 3;
			setEffect = true;
		}
	}

	if (curDeathPlatformCD <= 0 && !setEffect) {
		printf("Rolling for DEATH!\n");
		chance = rand() % 100;
		if (chance < deathPlatformChance) {
			curDeathPlatformCD = deathPlatformCD;
			effect = 4;
			setEffect = true;
		}
	}

	if (curLifePlatformCD <= 0 && !setEffect && livesRemaining < 3) {
		printf("Rolling for DEATH!\n");
		chance = rand() % 100;
		if (chance < lifePlatformChance) {
			curLifePlatformCD = lifePlatformCD;
			effect = 5;
			setEffect = true;
		}
	}

	return effect;
}