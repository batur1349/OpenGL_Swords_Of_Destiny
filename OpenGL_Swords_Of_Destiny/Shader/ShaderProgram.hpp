#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

class ShaderProgram
{
public:
	// Constructor and ~Destructor
	ShaderProgram(const std::string& fileName);
	virtual ~ShaderProgram();
	// Functions
	inline void Start() { glUseProgram(m_programID); }
	inline void Stop() { glUseProgram(0); }
protected:
	// Functions
	void BindAttribute(const int& attribute, const std::string& variableName);
	GLuint GetUniformLocation(const std::string& uniformName);
	// GPU Data loaders
	void LoadFloat(const GLuint& location, const float& value);
	void LoadVector3F(const GLuint& location, const glm::vec3& vector);
	void LoadBool(const GLuint& location, const bool& value);
	void LoadMatrix4F(const GLuint& location, const glm::mat4& matrix, const bool& transpose = false);
	void LoadInt(const GLuint& location, const int& value);
	void LoadVector2F(const GLuint& location, const glm::vec2& vector);
	void LoadVector4F(const GLuint& location, const glm::vec4& vector);
private:
	static GLuint LoadShader(std::string fileName, GLenum type);

	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
};

#endif // !SHADERPROGRAM_HPP