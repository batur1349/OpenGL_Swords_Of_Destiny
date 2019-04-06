#include "../pch.h"
#include "Entity.hpp"

Entity::Entity(const Model & model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: _model(model), _position(position), _rotation(rotation), _scale(scale)
{

}

void Entity::Move(glm::vec3 movement)
{
	_position += movement;
}

void Entity::Rotate(glm::vec3 rotation)
{
	_rotation += rotation;
}
