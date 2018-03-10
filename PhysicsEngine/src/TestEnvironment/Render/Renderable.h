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
	Renderable(const glm::vec4& color_, Mesh* mesh_, Shader& shader_)
		: color(color_) 
		, mesh(mesh_)
		, shader(&shader_)
	{
	}

	// Set visible
	void SetVisible(bool visible) { isVisible = visible; }

	// Render
	void Render(const glm::mat4& viewProjection, const Transform& transform)
	{
		if (!isVisible)
		{
			return;
		}

		// build the model
		glm::mat4 model = glm::mat4();
		model = glm::translate(model, transform.position)
			* glm::rotate(model, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::rotate(model, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::rotate(model, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
			* glm::scale(model, transform.scale);

		// set uniforms
		shader->SetUniform("modelViewProjection", viewProjection * model);
		shader->SetUniform("color", color);

		// render the mesh
		mesh->Render();
	}
};

#endif // !RENDERABLE_H

