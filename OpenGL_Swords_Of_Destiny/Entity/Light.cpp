#include "../pch.h"
#include "Light.hpp"


Light::Light(const glm::vec3& position, const glm::vec3& color)
{
	m_position = position;
	m_color = color;
}
