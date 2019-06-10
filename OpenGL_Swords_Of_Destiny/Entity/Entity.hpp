#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Entity/TexturedObject.hpp"

class Entity
{
public:
	// Constructor
	Entity(TexturedObject texModel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::pair<glm::vec3, glm::vec3> minmax);

	// Functions
	void Move(const glm::vec3& moveVector);
	void Move(const float& x, const float& y, const float& z);
	void Rotate(const glm::vec3& rotateVector);
	void Rotate(const float& rx, const float& ry, const float& rz);

	// Getters
	inline TexturedObject& GetTexturedObject() { return m_texturedObject; }
	inline glm::vec3& GetPosition() { return m_position; }
	inline glm::vec3& GetRotation() { return m_rotation; }
	inline glm::vec3& GetScale() { return m_scale; }
	inline glm::vec3& GetBounds(const int& index) { return bounds[index]; }
	inline bool& GetSelected() { return m_selected; }

	// Setters
	inline void SetPosition(const glm::vec3& position) { m_position = position; }
	inline void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
	inline void SetScale(const glm::vec3& scale) { m_scale = scale; }
	inline void SetSelected(const bool& selected) { m_selected = selected; }
private:
	// Variables
	TexturedObject m_texturedObject;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	// Bounding Box Variables
	bool m_selected = false;
	glm::vec3 bounds[2];
};
#endif // !ENTITY_HPP