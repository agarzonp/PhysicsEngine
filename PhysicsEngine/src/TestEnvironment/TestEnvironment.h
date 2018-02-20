#ifndef TEST_ENVIRONMENT_H
#define TEST_ENVIRONMENT_H

#include <cassert>
#include <memory>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include "../Input/Input.h"
#include "../Shaders/Shader.h"
#include "Camera/FreeCamera.h"

#include "GameObject.h"
#include "CubeRenderable.h"

#include "Physics/PhysicsEngine.h"

class TestEnvironment : public InputListener
{

public:
  TestEnvironment()
	{
		Init();
	}

	~TestEnvironment()
	{
		Terminate();
	}

	void OnKeyPressed(int key) override 
	{
	}

	void OnKeyReleased(int key) override { }
	void OnMouseButtonPressed(int button, double x, double y) override { }
	void OnMouseButtonReleased(int button, double x, double y) override { }
	void OnMouseScroll(double xoffset, double yoffset) override { }
	
	void OnMouseMove(double x, double y) { }

	void Update(float deltaTime) 
	{
    camera.Update(deltaTime);

		physicsEngine.Update(deltaTime);
	}

	void Render() 
	{
		DrawGameObjects();
	}
	
protected:

	void Init()
	{
		// init the vertex buffer object
		InitVBO();

		// init the indeces buffer object
		InitIBO();

		// init the vertex array object
		InitVAO();

		// load shader
		shader.Load("assets/Shaders/basic.vert", "assets/Shaders/basic.frag");

		// init game objects
		InitGameObjects();

    // init camera
    camera.Init(glm::vec3(0.0f, 1.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 1024.0f / 768.0f, 0.1f, 1000000.0f);

		// init physics
		InitPhysics();
	}
		
	void InitVBO()
	{
		// create one buffer in the GPU, use it as an array buffer and set the data
		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	void InitIBO()
	{
		// create one buffer in the GPU, use it as an element array buffer and set the data
		glGenBuffers(1, &indexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void InitVAO()
	{
		// create one vertex array object for drawing and use it. This vertexArrayObject is the one who will deal with the vertex buffer
		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

		// Tell the vertex shader how to interpret the buffer data. This information is needed for the active vertexArrayObject
		// The 0 attribute(pos) has 3 elements (x,y,z) of type GL_FLOAT
		// The stride to the next 0 attribute is zero bytes because there are no other attributes in between
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		// Enable the 0 attribute
		glEnableVertexAttribArray(0);
	}

	void InitGameObjects()
	{
		GameObject gameObject;

		// floor
		gameObject.Transform().position = glm::vec3(0.0f, 0.0f, 10.0f);
		gameObject.Transform().scale = glm::vec3(40.0f, 0.0001f, 40.f);
		gameObject.SetRenderable(CubeRenderable(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);

		// walls
		gameObject.Transform().position = glm::vec3(40.0f, 5.0f, 10.0f);
		gameObject.Transform().scale = glm::vec3(0.5f, 5.0f, 40.f);
		gameObject.SetRenderable(CubeRenderable(glm::vec4(0.11f, 0.11f, 0.11f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);

		gameObject.Transform().position = glm::vec3(-40.0f, 5.0f, 10.0f);
		gameObject.Transform().scale = glm::vec3(0.5f, 5.0f, 40.f);
		gameObject.SetRenderable(CubeRenderable(glm::vec4(0.11f, 0.11f, 0.11f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);

		gameObject.Transform().position = glm::vec3(0.0f, 5.0f, 50.0f);
		gameObject.Transform().scale = glm::vec3(40.0f, 5.0f, 0.5f);
		gameObject.SetRenderable(CubeRenderable(glm::vec4(0.11f, 0.11f, 0.11f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);

		gameObject.Transform().position = glm::vec3(0.0f, 5.0f, -30.0f);
		gameObject.Transform().scale = glm::vec3(40.0f, 5.0f, 0.5f);
		gameObject.SetRenderable(CubeRenderable(glm::vec4(0.11f, 0.11f, 0.11f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);

		// red cubes

		gameObject.Transform().position = glm::vec3(-20.0f, 2.5f, -18.0f);
		gameObject.Transform().rotation = glm::vec3(0.5f, 0.5f, 0.0f);
		gameObject.Transform().scale = glm::vec3(2.5f, 2.5f, 2.5f);
		gameObject.SetRenderable(CubeRenderable(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);

		gameObject.Transform().position = glm::vec3(25.0f, 2.5f, 40.0f);
		gameObject.Transform().rotation = glm::vec3(0.5f, 0.5f, 0.0f);
		gameObject.Transform().scale = glm::vec3(2.5f, 2.5f, 2.5f);
		gameObject.SetRenderable(CubeRenderable(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);
	}

	void DrawGameObjects()
	{
		const glm::mat4& viewProjection = camera.ViewProjectionMatrix();

		// use the shader
		shader.Use();	

		// tell the vertexArrayObject to be used
		glBindVertexArray(vertexArrayObject);

		glm::mat4 model;
		for (auto& gameObject : gameObjects)
		{
			if (gameObject.IsVisible())
			{
				model = glm::mat4();
				model = glm::translate(model, gameObject.Transform().position)
					* glm::rotate(model, gameObject.Transform().rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
					* glm::rotate(model, gameObject.Transform().rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
					* glm::rotate(model, gameObject.Transform().rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
					* glm::scale(model, gameObject.Transform().scale);
				shader.SetUniform("modelViewProjection", viewProjection * model);
				shader.SetUniform("color", gameObject.GetRenderable().Color());
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)indices); // tell to draw cube by using the IBO
			}
		}

		// do not use the vertexArrayObject anymore
		glBindVertexArray(0);
	}

	void InitPhysics()
	{
		PhysicObjectDesc desc;
		desc.type = PhysicObjectType::PARTICLE;
		desc.mass = 10.0f;
		desc.velocity = MathGeom::Vector3(-2.0f, 0.0f, 0.0f);
		desc.acceleration = MathGeom::Vector3(-10.0f, 0.0f, 0.0f);

		auto physicObject = physicsEngine.AddPhysics(gameObjects[6], desc);
		gameObjects[6].SetPhysicObject(physicObject);
	}

	void Terminate()
	{
		glDeleteVertexArrays(1, &vertexArrayObject);
		glDeleteBuffers(1, &vertexBufferObject);
		glDeleteBuffers(1, &indexBufferObject);
	}

private:

	// vertices of the cube
	GLfloat vertices[24] =
	{
		-1.0f,	1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,	1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f
	};


	// indices to cube vertices
	GLuint indices[36] =
	{
	   // tri 1      tri 2
		0, 2, 1,		0, 3, 2,	// front face
		4, 6, 5,    4, 7, 6,	// back face	
		4, 3, 0,    4, 7, 3,	// left face	
		1, 6, 5,    1, 2, 6,	// right face	
		4, 1, 5,    4, 0, 1,	// top face	
		7, 2, 6,    7, 3, 2		// bottom face	
	};
	
	// vbo, vao, ibo 
	GLuint vertexBufferObject;
	GLuint indexBufferObject;
	GLuint vertexArrayObject; 
	
	// shader
	Shader shader;

  // Camera
  FreeCamera camera;

	// game objects
	std::vector<GameObject> gameObjects;

	// Physics engine
	PhysicsEngine physicsEngine;
};

#endif