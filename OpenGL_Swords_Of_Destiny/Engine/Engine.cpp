#include "../pch.h"
#include "Engine.hpp"

Engine::Engine()
{
	// Initialize the variables
	_deltaTime = 0.0f;
	_lastFrame = 0.0f;
	_window = nullptr;

	// Initialized GLFW
	if (glfwInit())
	{
		// Print the GLFW success
		std::cout << "GLFW initialized successfully" << std::endl;

		// Create the display manager (pointers must be deleted)
		_window = new Window(800, 600, "Barbaros OpenGL 3D Engine");

		// Initialize glew using experimental
		glewExperimental = true;

		// Initialize the glew
		GLenum status = glewInit();

		// Check if the GLEW has initialized
		if (status == GLEW_OK)
		{
			// Print the GLEW success
			std::cout << "GLEW initialized successfully" << std::endl;
		}
		else
		{
			// Print the GLEW didn't initialized properly
			std::cerr << "ERROR: GLEW failed to initialize \n" << glewGetErrorString(status) << std::endl;
		}
	}
	else
	{
		// Print the GLFW didn't initialized properly
		std::cerr << "ERROR: GLFW failed to initialize" << std::endl;
	}
}

Engine::~Engine()
{
	// Delete the window 
	delete _window;

	// Cleanup the GLFW stuff
	glfwTerminate();
}

void Engine::Run()
{
	ThirdPersonCamera camera;
	Loader loader;
	MasterRenderer renderer(_window->GetAspectRatio(), loader);

	Object simple = loader.LoadAssimpObjFile("lowPolyTree");
	Texture test = loader.LoadTexture2D("lowPolyTree");
	TexturedObject myFirstObject = TexturedObject(simple, test);
	Entity myFirstEntity = Entity(myFirstObject, glm::vec3(0), glm::vec3(0), glm::vec3(0.1));

	std::vector<glm::vec3> tileVert = { glm::vec3(-1, 0, -1), glm::vec3(-1, 0, 1), glm::vec3(1, 0, 1), glm::vec3(1, 0, -1) };
	std::vector<glm::vec2> tileUvs = { glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 0), glm::vec2(1, 1) };
	std::vector<glm::vec3> tileNormals = { glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0) };
	std::vector<int> tileIndices = { 0, 1, 2, 2, 3, 0 };
	Object tileObj = loader.LoadToVAO(tileVert, tileUvs, tileNormals, tileIndices);
	Texture tileTex = loader.LoadTexture2D("grass2");
	TexturedObject tileTexObj = TexturedObject(tileObj, tileTex);

	std::vector<Tile> tiles;
	//Tile myFirstTile("grass2", glm::vec3(0, 0, 0), loader);
	//tiles.push_back(myFirstTile);
	float six = 2, adet = 40;
	for (float i = 0; i < adet; i++)
	{
		for (float j = 0; j < adet; j++)
		{
			tiles.push_back(Tile(tileTexObj, glm::vec3(i * six, 0, j * six)));
		}
	}

	float x, y, z;
	std::vector<Entity> entities;
	for (int i = 0; i < 100; i++)
	{
		x = rand() % 100;
		y = 0;
		z = rand() % 100;

		entities.emplace_back(myFirstObject, glm::vec3(x, y, z), glm::vec3(0), glm::vec3(0.2));
	}
	entities.clear();

	while (_window->IsOpen())
	{
		// Update the deltaTime 
		UpdateDeltatime();

		// Update the camera
		camera.Update(_deltaTime);

		// Render
		renderer.Prepare();
		//renderer.Render(entities, terrains, camera);
		renderer.Render(entities, tiles, camera);

		// Update the window
		_window->Update();

		// If escape key has pressed, close the window
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			_window->Close();
	}
}

void Engine::UpdateDeltatime()
{
	// Get the current frame time
	float currentFrame = glfwGetTime();

	// Calculate the delta time
	_deltaTime = currentFrame - _lastFrame;

	// Set the last frame
	_lastFrame = currentFrame;

	// Update the window's ms title
	_window->SetMsTitle(std::to_string(_deltaTime * 1000.0f));
}