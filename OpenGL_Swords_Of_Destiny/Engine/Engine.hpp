#ifndef ENGINE_H
#define ENGINE_H

#include "../Window/Window.hpp"
#include "../Renderer/MasterRenderer.hpp"
#include "../Entity/ThirdPersonCamera.hpp"

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
	glm::vec2 _mousePositionScreen;
	Window* _window;
};
#endif // !ENGINE_H