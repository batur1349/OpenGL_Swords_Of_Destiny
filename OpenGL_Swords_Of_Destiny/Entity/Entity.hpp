#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Entity/TexturedObject.hpp"

class Entity
{
public:
	// Constructor
	Entity(TexturedObject texModel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	// Functions
	void Move(const glm::vec3& moveVector);
	void Move(const float& x, const float& y, const float& z);
	void Rotate(const glm::vec3& rotateVector);
	void Rotate(const float& rx, const float& ry, const float& rz);

	// Getters
	inline TexturedObject& GetTexturedModel() { return m_texturedModel; }
	inline glm::vec3& GetPosition() { return m_position; }
	inline glm::vec3& GetRotation() { return m_rotation; }
	inline glm::vec3& GetScale() { return m_scale; }

	// Setters
	inline void SetPosition(const glm::vec3& position) { m_position = position; }
	inline void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
	inline void SetScale(const glm::vec3& scale) { m_scale = scale; }
private:
	// Variables
	TexturedObject m_texturedModel;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};
#endif // !ENTITY_HPP