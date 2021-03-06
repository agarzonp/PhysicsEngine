#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../Transform.h"
#include "Meshes/Mesh.h"

class Renderable
{
	// Mesh
	Mesh* mesh { nullptr };

	// shader
	Shader* shader { nullptr };

	// isVisible
	bool isVisible{ false };

	// color
	glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

public:
	// Constructors
	Renderable() = default;
	Renderable(Mesh* mesh_, Shader& shader_, const glm::vec4& color_)
		: mesh(mesh_)
		, shader(&shader_)
		, color(color_)
	{
	}

	virtual ~Renderable(){}

	glm::vec4& Color() { return color; }

	// Set visible
	void SetVisible(bool visible) { isVisible = visible; }

	// Render
	void Render(const glm::mat4& viewProjection, const Transform& transform)
	{
		if (!isVisible)
		{
			return;
		}

		// build the model matrix
		glm::mat4 model = ModelMatrix(transform);

		// set uniforms
		shader->SetUniform("modelViewProjection", viewProjection * model);
		shader->SetUniform("color", color);

		// render the mesh
		mesh->Render();
	}

protected:

	virtual glm::mat4 ModelMatrix(const Transform& transform)
	{
		glm::mat4 model = glm::mat4();
		model = glm::translate(model, transform.position) * transform.RotationMatrix4() * glm::scale(model, transform.scale);	
		return model;
	}
};

#endif // !RENDERABLE_H

