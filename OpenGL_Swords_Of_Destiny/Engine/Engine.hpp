#ifndef ENGINE_H
#define ENGINE_H

#include "../Window/Window.hpp"

// TODO1 - GUI
enum EngineState { RUNNING, PAUSED };
enum RunningState { GAMESTATE, EDITORSTATE };

class Engine
{
public:
	// Constructor & ~Destructor
	Engine();
	~Engine();
	// Functions
	void Run();
private:
	// Functions
	void UpdateDeltatime();
	// Variables
	float _deltaTime;
	float _lastFrame;
	Window* _window;
};
#endif // !ENGINE_H