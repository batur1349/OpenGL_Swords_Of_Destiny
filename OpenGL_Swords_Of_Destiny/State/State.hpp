#ifndef STATE_HPP
#define STATE_HPP

#include "../Window/Window.hpp"

class State
{
public:
	// Constructor and ~Destructor
	State(Window* window, std::stack<State*>* statesPtr);
	virtual ~State();

	// Getters
	const bool& GetQuit() const;
	const bool GetKeytime();
	const glm::vec2& GetMousePositionScreen() const;
	const glm::vec2& GetMousePositionWindow() const;

	// Setters
	virtual void SetStates(std::stack<State*>* ptr);

	// Functions
	void EndState();
	void PauseState();
	void UnpauseState();

	virtual void Update(const float& dt);
	virtual void UpdateMousePositions();
	virtual void UpdateKeytime(const float& dt);
	virtual void UpdateInput(const float& dt) = 0;
	virtual void Render() = 0;
protected:
	// Variables
	Window* _window;

	bool _quit, _paused;
	std::stack<State*> *_states;
	float _keytime, _keytimeMax;

	glm::vec2 _mousePositionWindow;
	glm::vec2 _mousePositionScreen;
	glm::vec2 _mousePositionOpenGL;
};

#endif // !STATE_HPP