#include "../pch.h"
#include "Engine.hpp"


Engine::Engine()
{
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
	// TEMPORARY DELETE LATER FOR TESTING
	State state(_window);

	while (_window->IsOpen())
	{
		// Update the deltaTime 
		UpdateDeltatime();

		// Update the state
		state.Update(_deltaTime);

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