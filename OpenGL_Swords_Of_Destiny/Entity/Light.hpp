#ifndef LIGHT_HPP
#define LIGHT_HPP

class Light
{
public:
	Light(const glm::vec3& position, const glm::vec3& color);

	// Getters
	inline glm::vec3& GetPosition() { return m_position; }
	inline glm::vec3& GetColor() { return m_color; }

	// Setters
	inline void SetPosition(const glm::vec3& position) { m_position = position; }
	inline void SetColor(const glm::vec3& color) { m_color = color; }
private:
	glm::vec3 m_position, m_color;
};

#endif // !LIGHT_HPP