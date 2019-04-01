#ifndef BASEMODEL_HPP
#define BASEMODEL_HPP

class BaseModel
{
public:
	// Constructor
	BaseModel(GLuint & vaoID, int vertexCount);

	// Getters
	inline GLuint GetVaoID() { return _vaoID; }
	inline int GetVertexCount() { return _vertexCount; }

	// Functions
	void Render();
private:
	GLuint _vaoID;
	int _vertexCount;
};

#endif // !BASEMODEL_HPP