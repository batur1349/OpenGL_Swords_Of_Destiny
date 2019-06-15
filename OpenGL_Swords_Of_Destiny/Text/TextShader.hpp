#ifndef TEXTSHADER_HPP
#define TEXTSHADER_HPP

class TextShader
{
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	TextShader(const GLchar* vertexPath, const GLchar* fragmentPath);

	// use/activate the shader
	void Start() { glUseProgram(ID); }
	void Stop() { glUseProgram(0); }
	// utility uniform functions
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMat4(const std::string& name, glm::mat4 matrix) const;
	void SetVec3(const std::string& name, glm::vec3 vector) const;
private:
	void GetAllUniformLocation();

	GLuint textColor_Location, projection_Location;
};

#endif // !TEXTSHADER_HPP