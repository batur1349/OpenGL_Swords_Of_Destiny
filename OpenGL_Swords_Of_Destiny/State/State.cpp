#include "../pch.h"
#include "State.hpp"


State::State(Window * window, std::stack<State*> * statesPtr)
	: _states(statesPtr)
{
	_window = window;
	_quit = false;
	_paused = false;
	_keytime = 0.0f;
	_keytimeMax = 0.2f;
}

State::~State()
{
}

const bool & State::GetQuit() const
{
	return _quit;
}

const bool State::GetKeytime()
{
	if (_keytime >= _keytimeMax)
	{
		_keytime = 0.0f;
		return true;
	}

	return false;
}

const glm::vec2 & State::GetMousePositionScreen() const
{
	return _mousePositionScreen;
}

const glm::vec2 & State::GetMousePositionWindow() const
{
	return _mousePositionWindow;
}

void State::SetStates(std::stack<State*>* ptr)
{
	_states = ptr;
}

void State::EndState()
{
	_quit = true;
}

void State::PauseState()
{
	_paused = true;
}

void State::UnpauseState()
{
	_paused = false;
}

void State::Update(const float & dt)
{
	UpdateInput(dt);
	UpdateKeytime(dt);
	UpdateMousePositions();
}

void State::UpdateMousePositions()
{
	_mousePositionScreen = _window->GetMousepositionScreen();
	_mousePositionWindow = _window->GetMousepositionWindow();
	_mousePositionOpenGL = _window->GetMousepositionOpenGL();
}

void State::UpdateKeytime(const float & dt)
{
	if (_keytime < _keytimeMax)
		_keytime += dt;
}

void State::UpdateInput(const float & dt)
{
	//// Testing purposes
	//if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) && GetKeytime())
	//{
	//	std::cout << "UP KEY PRESSED" << std::endl;
	//}
}