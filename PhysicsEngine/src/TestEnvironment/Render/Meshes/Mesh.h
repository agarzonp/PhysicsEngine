#ifndef MESH_H
#define MESH_H

class Mesh
{
protected:

	// vbo, vao, ibo 
	GLuint vertexBufferObject;
	GLuint indexBufferObject;
	GLuint vertexArrayObject;

	GLsizei numVBO{ 1 };
	GLsizei numIBO{ 1 };
	GLsizei numVAO{ 1 };

public:
	virtual ~Mesh() { Terminate(); }

	// Init
	void Init()
	{
		InitVBO();
		InitIBO();
		InitVAO();
	}

	// Render
	virtual void Render() = 0;

protected:

	// Terminate
	void Terminate()
	{
		glDeleteVertexArrays(numVAO, &vertexArrayObject);
		glDeleteBuffers(numIBO, &indexBufferObject);
		glDeleteBuffers(numVBO, &vertexBufferObject);
	}

	virtual void InitVBO() = 0;
	virtual void InitIBO() = 0;
	virtual void InitVAO() = 0;
};

#endif // !MESH_H

