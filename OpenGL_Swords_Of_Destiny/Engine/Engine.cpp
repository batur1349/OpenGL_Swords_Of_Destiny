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

	// Initialize the basic triangle
	InitializeBasicTriangle();

	// Initialize the basic quad
	InitializeBasicQuad();

	while (_window->IsOpen())
	{
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.4f, 0.5f);

		// Draw the basic triangle
		DrawBasicTriangle();

		// Draw the basic quad
		DrawBasicQuad();

		// Update the deltaTime 
		UpdateDeltatime();

		// Update the states
		UpdateStates();

		// Render the states
		RenderStates();

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

void Engine::InitializeBasicTriangle()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	   0.0f, -1.0f, 0.0f,	// Bot left
	   1.0f, -1.0f, 0.0f,	// Bot right
	   0.5f,  0.5f, 0.0f,	// Top point
	};

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &_vertexbuffer[0]);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer[0]);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Engine::InitializeBasicQuad()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-0.6f, 0.6f, 0.0f,
		-0.6f, -0.6f, 0.0f,
		0.0f, 0.6f, 0.0f,

		0.0f, 0.6f, 0.0f,
		-0.6f, -0.6f, 0.0f,
		0.0f, -0.6f, 0.0f
	};

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &_vertexbuffer[1]);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer[1]);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Engine::DrawBasicTriangle()
{
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer[0]);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

void Engine::DrawBasicQuad()
{
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer[1]);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
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