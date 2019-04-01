#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "../GameState/GameState.hpp"

class MainmenuState : public State
{
public:
	// Constructor and ~Destructor
	MainmenuState(Window* window, std::stack<State*>* statesPtr);
	virtual ~MainmenuState();

	// Functions
	void UpdateInput(const float& dt);
	void Update(const float& dt);
	void Render();
private:
	// Variables
};
#endif // !MAINMENUSTATE_HPP