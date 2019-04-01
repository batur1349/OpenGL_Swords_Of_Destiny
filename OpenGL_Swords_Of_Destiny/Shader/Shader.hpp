#ifndef SHADER_HPP
#define SHADER_HPP

class Shader
{
public:
	// Constructor and ~Destructor
	Shader(const std::string& fileName);
	virtual ~Shader();

	// Functions
	const inline void Start() const { glUseProgram(_programID); }
	const inline void Stop() const { glUseProgram(0); }
protected:
	// Functions
	void BindAttribute(int attribute, const std::string& variableName);
private:
	static GLuint LoadShader(std::string fileName, GLenum type);

	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

#endif // !SHADER_HPP