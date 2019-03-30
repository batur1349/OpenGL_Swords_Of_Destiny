#include "../pch.h"
#include "Window.hpp"


Window::Window(const unsigned int & width, const unsigned int & height, const std::string & title)
	: _screenWidth(width), _screenHeight(height), _frameLimit(0), _deltaTime(0.0f)
{
	// Set the windows title
	_title = title;
	// Set the aspect ratio of window
	_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	// Set minimum OpenGL version and options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Create the OpenGL window with GLFW
	_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	// Check if window was created
	if (_window != NULL)
	{
		std::cout << "Window created successfully" << std::endl;
		// Set OpenGL context to the window, it is needed for the GLEW initialization
		glfwMakeContextCurrent(_window);
		// Set OpenGL viewport to full size of the window
		glViewport(0, 0, width, height);
		// Enable vertical sync
		glfwSwapInterval(0);
		// Initialize the frames container
		_oldFrames.resize(FRAME_CONTAINER_SIZE);
		// Vector of doubles to count the fps ratio, fill with the 0s
		std::fill(_oldFrames.begin(), _oldFrames.end(), 0.0f);
	}
	else
	{
		// Check if GLFW is not initialized yet
		if (GLFW_NOT_INITIALIZED)
		{
			std::cerr << "ERROR: GLFW is not initialized!" << std::endl;
		}
		else
		{
			std::cerr << "ERROR: Failed to create window" << std::endl;
		}
	}
}

Window::~Window()
{
	std::cout << "Window destroyed! << Window::~Window()" << std::endl;
	glfwDestroyWindow(_window);
}

void Window::Close()
{
	glfwSetWindowShouldClose(_window, GL_TRUE);
}

void Window::Update()
{
	// Update the FPS counter
	ShowFps();
	// Tell GLFW to swap buffers so the old frame will be removed and new frame will be displayed
	glfwSwapBuffers(_window);
	// Tell GLFW to get window events so we can pull the window, interect with mouse and keyboard so on
	glfwPollEvents();
}

void Window::ShowFps()
{
	// Variables to computer frame render time
	static float previousFrame = 0.0;
	float currentFrame = glfwGetTime();
	float average = 0.0;

	// Change the values in the vector
	for (unsigned int i = 0; i < _oldFrames.size() - 1; i++)
	{
		_oldFrames.at(i) = _oldFrames.at(i + 1);
		average += _oldFrames.at(i);
	}

	// Store the new time in the last slot of vector
	_oldFrames.at(_oldFrames.size() - 1) = currentFrame - previousFrame;

	// Add the new time to the average
	average += _oldFrames.at(_oldFrames.size() - 1);

	// Divide average my the array size to get the average time
	average /= _oldFrames.size();

	// Calculate the ms [Currently calculating in the engine class]
	//_deltaTime = currentFrame - previousFrame;
	//_msTitle = std::to_string(_deltaTime * 1000.0f);

	// Update the title with the FPS
	glfwSetWindowTitle(_window, (_title + " | FPS: " + std::to_string(1.0f / average) + " | MS: " + _msTitle).c_str());

	// Store the current time
	previousFrame = currentFrame;
}

const bool & Window::IsOpen() const
{
	if (_frameLimit != 0)
	{
		if (static_cast<int>(std::trunc(_deltaTime)) <= std::ceil(static_cast<int>(1000.0f / _frameLimit)))
		{
			Sleep(std::trunc(static_cast<int>(1000.0f / _frameLimit) - _deltaTime));
		}
	}
	// If the close flag didn't issued to the window return the opposite of the closing state
	return !glfwWindowShouldClose(_window);
}

const float & Window::GetAspectRatio() const
{
	return _aspectRatio;
}

const float & Window::GetDeltatime() const
{
	return _deltaTime;
}

const unsigned int & Window::GetFramelimit() const
{
	return _frameLimit;
}

void Window::SetMsTitle(const std::string & msTitle)
{
	// Set the ms value to the title
	_msTitle = msTitle;
}

void Window::SetSize(const unsigned int & width, const unsigned int & height)
{
	// Set the aspect ratio of window
	_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	// Set the window size
	glfwSetWindowSize(_window, width, height);
	// Change the private variables
	_screenWidth = width; _screenHeight = height;
}

void Window::SetVsync(const unsigned int & value)
{
	glfwSwapInterval(value);
}

void Window::SetFramelimit(const unsigned int & limit)
{
	_frameLimit = limit;
}
