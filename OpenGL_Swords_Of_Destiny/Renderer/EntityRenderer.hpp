#ifndef ENTITYRENDERER_HPP
#define ENTITYRENDERER_HPP

#include "../Maths/Maths.hpp"
#include "../Entity/TexturedObject.hpp"
#include "../Shader/GeneralShader.hpp"
#include "../Entity/Entity.hpp"

#include "Frustum.hpp"

struct TextureObjectCompare
{
public:
	bool operator() (TexturedObject t1, TexturedObject t2) const
	{
		return ((t1.GetModelObject().GetVaoID() < t2.GetModelObject().GetVaoID()) ||
			(t1.GetModelTexture().GetTextureID() < t2.GetModelTexture().GetTextureID()));
	}
};

class EntityRenderer
{
public:
	// Constructor
	EntityRenderer(GeneralShader& shader, const glm::mat4& projectionMatrix);

	// Functions
	void RenderEntities(std::map<TexturedObject, std::vector<Entity>, TextureObjectCompare>& entities);
	void EnableCulling();
	void DisableCulling();
private:
	// Functions
	void BindTexturedObject(TexturedObject texturedObject);
	void UnbindTexturedModel();
	void RenderEntity(Entity& entity);

	// Variables
	GeneralShader& m_shader;
};

#endif // !ENTITYRENDERER_HPP