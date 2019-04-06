#ifndef SHADER_HPP
#define SHADER_HPP

class Shader
{
public:
	// Constructor and ~Destructor
	Shader(const std::string& fileName);
	virtual ~Shader();

	// Functions
	inline void Start() { glUseProgram(_programID); }
	inline void Stop() { glUseProgram(0); }
protected:
	// Functions
	void BindAttribute(int attribute, const std::string& variableName);
	GLuint GetUniformLocation(const std::string& uniformName);
	// GPU Data loaders
	void LoadFloat(GLuint location, const float& value);
	void LoadVector3F(GLuint location, const glm::vec3& vector);
	void LoadBoolean(GLuint location, const bool& value);
	void LoadMatrix4f(GLuint location, const glm::mat4& matrix, const bool& transpose = false);
private:
	static GLuint LoadShader(std::string fileName, GLenum type);

	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

#endif // !SHADER_HPP