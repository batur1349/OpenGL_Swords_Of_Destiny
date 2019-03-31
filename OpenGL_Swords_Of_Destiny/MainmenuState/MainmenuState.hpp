#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "../GameState/GameState.hpp"

class MainmenuState : public State
{
public:
	MainmenuState(Window* window, std::stack<State*>* statesPtr);
	virtual ~MainmenuState();

	void UpdateInput(const float& dt);
	void Update(const float& dt);
	void Render();
private:
};

#endif // !MAINMENUSTATE_HPP