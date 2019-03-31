#include "../pch.h"
#include "MainmenuState.hpp"


MainmenuState::MainmenuState(Window * window, std::stack<State*> * statesPtr)
	: State(window, statesPtr)
{

}

MainmenuState::~MainmenuState()
{

}

void MainmenuState::UpdateInput(const float & dt)
{
	// New game
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) && GetKeytime())
	{
		_states->push(new GameState(_window, _states));
		std::cout << "GameState pushed!" << std::endl;
		std::cout << "States Size :" << _states->size() << std::endl;
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_C) && GetKeytime())
	{
		_quit = true;
		std::cout << "Closing MainmenuState!" << std::endl;
		std::cout << "States Size :" << _states->size() - 1 << std::endl;
	}
}

void MainmenuState::Update(const float & dt)
{
	UpdateInput(dt);

	UpdateKeytime(dt);

	UpdateMousePositions();
}

void MainmenuState::Render()
{
}
