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
	Loader loader;
	ResourceManager resourceManager;
	MasterRenderer renderer(_window->GetAspectRatio(), loader);
	ThirdPersonCamera camera(glm::vec3(0, 0, 0), glm::vec3(0));

	std::vector<Tile> tiles = resourceManager.GenerateTilemap();
	std::vector<Entity> entities = resourceManager.GenerateEntities();
	std::vector<GuiTexture> guis = resourceManager.GenerateGuiTextures();
	std::map<std::string, Texture> tileTextures = resourceManager.GenerateTileTextures();
	std::map<GLuint, std::vector<glm::vec3>> objectVertices = resourceManager.GetObjectVertices();
	std::map<GLuint, std::pair<glm::vec3, glm::vec3>> objectBounds = resourceManager.GetObjectBounds();

	MousePicker mousePicker(&camera, &tiles, &entities, &objectBounds);

	Light sun(glm::vec3(2000.0f, 2000.0f, 2000.0f), glm::vec3(1.0f));
	std::vector<Light> lights;
	lights.push_back(sun);

	while (_window->IsOpen())
	{
		// Update the deltaTime 
		UpdateDeltatime();

		// Update the camera
		camera.Update(_deltaTime);

		// Update the mouse
		mousePicker.Update(_deltaTime);

		// Render
		renderer.Render(entities, tiles, guis, lights, camera, tileTextures);

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