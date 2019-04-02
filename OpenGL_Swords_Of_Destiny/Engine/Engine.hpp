#ifndef ENGINE_H
#define ENGINE_H

#include "../Window/Window.hpp"
class Window;
#include "../MainmenuState/MainmenuState.hpp"
class MainmenuState;
class State;
#include "../Shader/BasicShader.hpp"
class BasicShader;
#include "../Loader/Loader.hpp"
class Loader;
class BaseModel;
#include "../Renderer/MasterRenderer.hpp"
class MasterRenderer;
//class BaseModel;
#include "../Texture/Texture.hpp"
class Texture;

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
	void UpdateDeltatime();

	// Variables
	float				_deltaTime;
	float				_lastFrame;
	glm::vec2			_mousePositionScreen;
	Window*				_window;
	std::stack<State*>	_states;
};
#endif // !ENGINE_H