#include "../pch.h"
#include "MainmenuState.hpp"


MainmenuState::MainmenuState(Window * window, std::stack<State*> * statesPtr)
	: State(window, statesPtr)
{
	_shapeCount = 0;
	_pointsCount = 0;
}

MainmenuState::~MainmenuState()
{

}

void MainmenuState::UpdateInput(const float & dt)
{
	// New game
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) && GetKeytime())
	{
		_states->push(new GameState(_window, _states));
		std::cout << "GameState pushed!" << std::endl;
		std::cout << "States Size :" << _states->size() << std::endl;
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_C) && GetKeytime())
	{
		_quit = true;
		std::cout << "Closing MainmenuState!" << std::endl;
		std::cout << "States Size :" << _states->size() - 1 << std::endl;
	}

	// MOUSE INPUT TEST
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) && GetKeytime())
	{
		// Increase the point count of shape
		_pointsCount++;
		std::cout << "MainmenuState::Mouse Left Pressed!" << std::endl;

		if (_pointsCount >= 3)
		{
			// Push back the opengl mouse positions
			_points.push_back(glm::vec3(_mousePositionOpenGL.x, _mousePositionOpenGL.y, 0.0f));

			// Push back the last point and first point
			_points.push_back(_points.back());
			_points.push_back(_points.at(0));
		}
		else
		{
			// Push back the opengl mouse position
			_points.push_back(glm::vec3(_mousePositionOpenGL.x, _mousePositionOpenGL.y, 0.0f));
		}
	}
	else if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) && GetKeytime())
	{
		std::cout << "MainmenuState::Mouse Right Pressed!" << std::endl;

		// Finish the shape with first point
		_points.push_back(_points.back());
		_points.push_back(_points.at(0));

		// Inýtialize the shape
		InitializeShape();

		// Reset the points count
		_pointsCount = 0;

		std::cout << "Shape count :" << _shapeCount;
	}
}

void MainmenuState::Update(const float & dt)
{
	UpdateInput(dt);

	UpdateKeytime(dt);

	UpdateMousePositions();
}

void MainmenuState::Render()
{
	DrawShapes();
}

void MainmenuState::InitializeShape()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create the vertex buffer object
	GLuint VBO;
	_vertexBuffer.push_back(VBO);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &_vertexBuffer[_shapeCount]);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer[_shapeCount]);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, _points.size() * sizeof(glm::vec3), _points.data(), GL_STATIC_DRAW);

	// Increase the shape count
	_shapeCount++;

	// Get the points vector 
	_pointsVec.push_back(_points);

	// Clear the points vector
	_points.clear();
}

void MainmenuState::DrawShapes()
{
	for (unsigned int i = 0; i < _vertexBuffer.size(); i++)
	{
		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer[i]);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, _pointsVec.at(i).size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);
	}
}
