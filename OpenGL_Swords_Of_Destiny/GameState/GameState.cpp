#include "../pch.h"
#include "GameState.hpp"


GameState::GameState(Window * window, std::stack<State*> * statesPtr)
	: State(window, statesPtr)
{

}

GameState::~GameState()
{

}

void GameState::UpdateInput(const float & dt)
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_C) && GetKeytime())
	{
		_quit = true;
		std::cout << "Closing GameState!" << std::endl;
		std::cout << "States Size :" << _states->size() - 1 << std::endl;
	}
}

void GameState::Update(const float & dt)
{
	UpdateKeytime(dt);

	UpdateInput(dt);
}

void GameState::Render()
{
}
