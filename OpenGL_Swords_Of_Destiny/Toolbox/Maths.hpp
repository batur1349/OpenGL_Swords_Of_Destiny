#ifndef MATHS_HPP
#define MATHS_HPP

#include "../Entity/Camera.hpp"

class Maths
{
public:
	static glm::mat4 CreateTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
	static glm::mat4 CreateViewMatrix(Camera camera);
private:
};

#endif // !MATHS_HPP