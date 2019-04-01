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

	// Cleanup the states
	while (!_states.empty())
	{
		// Delete the top state
		delete _states.top();
		// Pop the states
		_states.pop();
	}
}

void Engine::Run()
{
	// TESTING
	_states.push(new MainmenuState(_window, &_states));
	std::cout << "Pushing MainmenuState" << std::endl;
	std::cout << "States Size :" << _states.size() << std::endl;

	BasicShader basicShader;
	Loader loader;

	std::vector<glm::vec3> vertices = {
		glm::vec3(0.2f,0.2f,0.0f),
		glm::vec3(0.2f,-0.2f,0.0f),
		glm::vec3(0.0f,-0.2f,0.0f),
		glm::vec3(0.0f,0.2f,0.0f)
	};

	std::vector<int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	BaseModel model = loader.LoadToVAO(vertices, indices, vertices.size(), indices.size());

	while (_window->IsOpen())
	{
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.4f, 0.5f);

		// Update the deltaTime 
		UpdateDeltatime();

		// Update the states
		UpdateStates();

		// Start the shader
		basicShader.Start();

		// Render basemodel
		model.Render();

		// Render the states
		RenderStates();

		// Stop the shader
		basicShader.Stop();

		// Update the window
		_window->Update();

		// If escape key has pressed, close the window
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			_window->Close();
	}
}

void Engine::UpdateStates()
{
	if (!_states.empty())
	{
		_states.top()->Update(_deltaTime);

		if (_states.top()->GetQuit())
		{
			_states.top()->EndState();
			delete _states.top();
			_states.pop();
		}
	}
	else // Application End
	{
		_window->Close();
	}
}

void Engine::RenderStates()
{
	if (!_states.empty())
	{
		_states.top()->Render();
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