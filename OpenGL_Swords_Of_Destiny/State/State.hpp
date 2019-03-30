#ifndef STATE_HPP
#define STATE_HPP

#include "../Window/Window.hpp"

class State
{
public:
	// Constructor and ~Destructor
	State(Window* window);
	virtual ~State();

	// Getters
	const bool& GetQuit() const;
	const bool GetKeytime();
	const glm::vec2& GetMousePositionScreen() const;
	const glm::vec2& GetMousePositionWindow() const;

	// Functions
	void EndState();
	void PauseState();
	void UnpauseState();

	virtual void Update(const float& dt);
	virtual void UpdateMousePositions();
	virtual void UpdateKeytime(const float& dt);
	virtual void UpdateInput(const float& dt); // = 0; GOING TO MAKE THIS CLASS ABSTRACT
private:
	// Variables
	Window* _window;

	bool _quit, _paused;
	std::stack<State*> *_states;
	float _keytime, _keytimeMax;

	glm::vec2 _mousePositionWindow;
	glm::vec2 _mousePositionScreen;
};

#endif // !STATE_HPP