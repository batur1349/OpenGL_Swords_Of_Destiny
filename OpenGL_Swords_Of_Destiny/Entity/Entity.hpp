#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Model/Model.hpp"

class Entity
{
public:
	// Constructor
	Entity(const Model& model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	// Functions
	void Move(glm::vec3 movement);
	void Rotate(glm::vec3 rotation);

	// Getters
	inline glm::vec3 GetPosition() { return _position; }
	inline glm::vec3 GetRotation() { return _rotation; }
	inline glm::vec3 GetScale() { return _scale; }
	inline Model GetModel() { return _model; }

	// Setters
	void SetPosition(glm::vec3 pos) { _position = pos; }
	void SetRotation(glm::vec3 rot) { _rotation = rot; }
	void SetScale(glm::vec3 scale) { _scale = scale; }
private:
	// Variables
	Model _model;
	glm::vec3 _position, _rotation, _scale;
};

#endif // !ENTITY_HPP