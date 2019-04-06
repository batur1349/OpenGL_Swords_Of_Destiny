#ifndef MASTERRENDERER_HPP
#define MASTERRENDERER_HPP

#include "../Model/Model.hpp"
#include "../Entity/Entity.hpp"
#include "../Shader/BasicShader.hpp"
#include "../Toolbox/Maths.hpp"

class MasterRenderer
{
public:
	// Constructor and ~Destructor
	MasterRenderer(BasicShader& shader);
	virtual ~MasterRenderer();

	// Functions
	void Prepare();
	const void Render(Model& model) const;
	const void Render(Entity& entity, BasicShader& shader) const;
private:
	// Variables
	static constexpr float _FOV = 70.0f, _NEAR_PLANE = 0.1f, _FAR_PLANE = 1000.0f;
	glm::mat4 _projectionMatrix;

	// Functions
	void CreateProjectionMatrix();
};

#endif // !MASTERRENDERER_HPP