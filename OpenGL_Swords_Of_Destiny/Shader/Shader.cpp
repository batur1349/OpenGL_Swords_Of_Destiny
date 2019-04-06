#include "../pch.h"
#include "Shader.hpp"


Shader::Shader(const std::string & fileName)
{
	// Load shaders from file
	_vertexShaderID = LoadShader(fileName + ".vert", GL_VERTEX_SHADER);
	_fragmentShaderID = LoadShader(fileName + ".frag", GL_FRAGMENT_SHADER);

	// Create shader program
	_programID = glCreateProgram();

	// Attach the shaders to the program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	// Link the program
	glLinkProgram(_programID);
	glValidateProgram(_programID);

	// Check validation status
	GLint status;
	glGetProgramiv(_programID, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Get info log length
		GLint infoLogLength;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		// Get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(_programID, infoLogLength, NULL, infoLog);
		printf("ERROR: could not validate program \n%s\n", infoLog);
		// Delete the array
		delete[] infoLog;
	}
}

Shader::~Shader()
{
	// Make sure we are not using this shader
	Stop();
	// Detach the shaders from the program
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	// Delete the shaders
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
	// Delete the program
	glDeleteProgram(_programID);
}

void Shader::BindAttribute(int attribute, const std::string & variableName)
{
	glBindAttribLocation(_programID, attribute, variableName.c_str());
}

GLuint Shader::GetUniformLocation(const std::string & uniformName)
{
	return glGetUniformLocation(_programID, uniformName.c_str());
}

void Shader::LoadFloat(GLuint location, const float & value)
{
	glUniform1f(location, value);
}

void Shader::LoadVector3F(GLuint location, const glm::vec3 & vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::LoadBoolean(GLuint location, const bool & value)
{
	float toLoad = 0;
	if (value)
		toLoad = 1;

	glUniform1f(location, toLoad);
}

void Shader::LoadMatrix4f(GLuint location, const glm::mat4 & matrix, const bool & transpose)
{
	if (transpose)
		glUniformMatrix4fv(location, 1, GL_TRUE, glm::value_ptr(matrix));
	else
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint Shader::LoadShader(std::string fileName, GLenum type)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string shaderCode;
	std::fstream shaderFile;

	// ensures ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		shaderFile.open(fileName.c_str());

		if (!shaderFile.is_open())
			std::cout << "ERROR::SHADER::FILE_COULD_NOT_BE_OPENED! :" << fileName << std::endl;

		std::stringstream shaderStream;
		// Read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// Convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ :" << fileName << std::endl;
	}
	const GLchar* shaderCodeGLchar = shaderCode.c_str();

	// 2. Compile shaders
	GLuint shaderID;
	GLint success;
	GLchar infoLog[512];
	// Create Shader
	shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &shaderCodeGLchar, NULL);
	glCompileShader(shaderID);
	// Print compile errors if any
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		if (type == GL_VERTEX_SHADER)
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		else
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shaderID;
}
