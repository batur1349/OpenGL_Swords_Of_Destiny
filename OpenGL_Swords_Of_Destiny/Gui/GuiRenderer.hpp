#ifndef GUIRENDERER_HPP
#define GUIRENDERER_HPP

#include "GuiShader.hpp"
#include "GuiTexture.hpp"
#include "../Loader/Loader.hpp"
#include "../Maths/Maths.hpp"

class GuiRenderer
{
public:
	// Constructor and ~Destructor
	GuiRenderer(Loader& loader);
	~GuiRenderer();

	// Functions
	void Render(std::vector<GuiTexture>& guis);
private:
	// Variables
	GuiShader _shader;
	Object _object;

	// Functions
	Object ConstructObject(Loader& loader);
};

#endif // !GUIRENDERER_HPP