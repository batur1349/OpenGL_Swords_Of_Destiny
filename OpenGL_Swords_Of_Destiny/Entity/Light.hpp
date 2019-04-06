#ifndef LIGHT_HPP
#define LIGHT_HPP

class Light
{
public:
	// Constructor
	Light(const glm::vec3& position, const glm::vec3& color);

	// Getters
	inline glm::vec3 GetPosition() { return _position; }
	inline glm::vec3 GetColor() { return _color; }
private:
	// Variables
	glm::vec3 _position, _color;
};

#endif // !LIGHT_HPP