#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../State/State.hpp"

class GameState : public State
{
public:
	// Constructor and ~Destructor
	GameState(Window* window, std::stack<State*>* statesPtr);
	~GameState();

	// Functions
	void UpdateInput(const float& dt);
	void Update(const float& dt);
	void Render();
private:
	// Variables

};

#endif // !GAMESTATE_HPP