#ifndef ENGINE_H
#define ENGINE_H

#include "../Window/Window.hpp"
class Window;
#include "../MainmenuState/MainmenuState.hpp"
class MainmenuState;
class State;

// TODO1 - GUI
enum EngineStatus { RUNNING, PAUSED };
enum RunningState { GAMESTATE, EDITORSTATE };

class Engine
{
public:
	// Constructor & ~Destructor
	Engine();
	~Engine();

	// Functions
	void Run();
	void UpdateStates();
	void RenderStates();
private:
	// Functions
	void InitializeBasicTriangle();
	void InitializeBasicQuad();
	void DrawBasicTriangle();
	void DrawBasicQuad();
	void UpdateDeltatime();

	// Variables
	float				_deltaTime;
	float				_lastFrame;
	glm::vec2			_mousePositionScreen;
	Window*				_window;
	std::stack<State*>	_states;

	// TEST
	GLuint _vertexbuffer[2];
};
#endif // !ENGINE_H