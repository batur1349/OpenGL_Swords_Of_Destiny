#ifndef BASICSHADER_HPP
#define BASICSHADER_HPP

#include "Shader.hpp"

class BasicShader : public Shader
{
public:
	// Constructor
	BasicShader();
	BasicShader(const std::string& fileName);
protected:
	// Functions
	virtual void BindAttributes();
private:
};

#endif // !BASICSHADER_HPP