#include "../pch.h"
#include "Entity.hpp"


Entity::Entity(TexturedObject texModel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: m_texturedModel(texModel), m_position(position), m_rotation(rotation), m_scale(scale)
{

}

void Entity::Move(const glm::vec3& moveVector)
{
	m_position += moveVector;
}

void Entity::Move(const float& x, const float& y, const float& z)
{
	m_position += glm::vec3(x, y, z);
}

void Entity::Rotate(const glm::vec3& rotateVector)
{
	m_rotation += rotateVector;
}

void Entity::Rotate(const float& rx, const float& ry, const float& rz)
{
	m_rotation += glm::vec3(rx, ry, rz);
}

