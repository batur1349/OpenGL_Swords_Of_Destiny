#ifndef MASTERRENDERER_HPP
#define MASTERRENDERER_HPP

#include "../Loader/Loader.hpp"
#include "../Shader/GeneralShader.hpp"
#include "../Entity/Entity.hpp"
#include "../Maths/Maths.hpp"

class MasterRenderer
{
public:
	// Constructor and ~Destructor
	MasterRenderer(float aspect, Loader& loader);
	virtual ~MasterRenderer();

	// Functions
	void Prepare();
	void Render(Entity& entity, ThirdPersonCamera& camera);

	// Getters
	inline glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }
private:
	// Variables
	const float m_FOV = 70;
	const float m_NEAR_PLANE = 0.1f;
	const float m_FAR_PLANE = 1000;
	const float RED = 0.5444f, GREEN = 0.62f, BLUE = 0.69f;
	glm::mat4 m_projectionMatrix;

	GeneralShader m_shader;
};

#endif // !MASTERRENDERER_HPP