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
	// Destroy the window
	glfwDestroyWindow(_window);
}

void Window::Close()
{
	// Order to window close
	glfwSetWindowShouldClose(_window, GL_TRUE);
}

void Window::Update()
{
	// Update the FPS counter
	ShowFps();

	// Update the mouse position
	UpdateMousepositions();

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

	// Update the title with the FPS
	glfwSetWindowTitle(_window, (_title + " | FPS: " + std::to_string(1.0f / average) + " | MS: " + _msTitle).c_str());

	// Store the current time
	previousFrame = currentFrame;
}

const bool & Window::IsOpen() const
{
	// If frame limit has set sleep the thread
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

const glm::vec2 & Window::GetMousepositionScreen() const
{
	return _mousePositionScreen;
}

const glm::vec2 & Window::GetMousepositionWindow() const
{
	return _mousePositionWindow;
}

const glm::vec2 & Window::GetMousepositionOpenGL() const
{
	return _mousePositionOpenGL;
}

const unsigned int & Window::GetScreenWidth() const
{
	return _screenWidth;
}

const unsigned int & Window::GetScreenHeight() const
{
	return _screenHeight;
}

void Window::SetMsTitle(const std::string & msTitle)
{
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

void Window::UpdateMousepositions()
{
	// Create temporal variables
	double posx = 0, posy = 0;
	int width = 0, height = 0;

	// Get the window constraits
	glfwGetWindowSize(_window, &width, &height);

	// Set the cursor input mode
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Get the cursor position
	glfwGetCursorPos(_window, &posx, &posy);

	// Set the class variable
	_mousePositionScreen = glm::vec2(posx, posy);

	// Check the window coordinates
	if (posx < 0) posx = 0;
	else if (posx > width) posx = width;
	if (posy < 0) posy = 0;
	else if (posy > height) posy = height;

	// Update the mouse positions
	_mousePositionWindow = glm::vec2(posx, posy);

	// Update the Opengl coordinated mouse position
	_mousePositionOpenGL.x = ((2 * ((_mousePositionWindow.x - 0.0f) / (_screenWidth - 0.0f))) - 1);
	_mousePositionOpenGL.y = ((2 * ((_mousePositionWindow.y - _screenHeight) / (0.0f - _screenHeight))) - 1);
}