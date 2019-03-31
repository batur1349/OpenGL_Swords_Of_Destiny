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
	// TEMPORAL 2D OBJECT BUILDER
	void InitializeShape();
	void DrawShapes();

	unsigned int _shapeCount;
	unsigned int _pointsCount;
	std::vector<GLuint> _vertexBuffer;
	std::vector<glm::vec3> _points;
	std::vector<std::vector<glm::vec3>> _pointsVec;
};

#endif // !MAINMENUSTATE_HPP