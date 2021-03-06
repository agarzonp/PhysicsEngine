#ifndef TEST_ENVIRONMENT_H
#define TEST_ENVIRONMENT_H

#include <cassert>
#include <memory>
#include <list>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include "../Input/Input.h"
#include "../Shaders/Shader.h"
#include "Camera/FreeCamera.h"

#include "GameObject.h"

#include "Render/Meshes/CubeMesh.h"
#include "Render/Meshes/SphereMesh.h"
#include "Render/Renderable.h"
#include "Render/SphereRenderable.h"
#include "Render/RenderUtils.h"

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
		switch (key)
		{
		case GLFW_KEY_C:
			PhysicsEngine::s_renderColliders = !PhysicsEngine::s_renderColliders;
			break;
		}
	}

	void OnKeyReleased(int key) override { }
	void OnMouseButtonPressed(int button, double x, double y) override { }
	void OnMouseButtonReleased(int button, double x, double y) override { }
	void OnMouseScroll(double xoffset, double yoffset) override { }
	
	void OnMouseMove(double x, double y) { }

	// Update
	void Update(float deltaTime) 
	{
		camera.Update(deltaTime);

		physicsEngine.Update(deltaTime);
	}

	// Render
	void Render() 
	{
		// use the shader
		shader.Use();

		// render game objects
		const glm::mat4& viewProjection = camera.ViewProjectionMatrix();
		for (auto& gameObject : gameObjects)
		{
			gameObject.Render(viewProjection);
		}

		// render physics
		physicsEngine.DebugRender(viewProjection);
	}
	
protected:

	void Init()
	{
		// init cube mesh
		cubeMesh.Init();
		sphereMesh.Init();

		// load shader
		shader.Load("assets/Shaders/basic.vert", "assets/Shaders/basic.frag");

		RenderUtils::InitCubeRenderable(shader, &cubeMesh);
		RenderUtils::InitSphereRenderable(shader, &sphereMesh);

		// init camera
		camera.Init(glm::vec3(-20.0f, 5.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 1024.0f / 768.0f, 0.1f, 1000000.0f);

		// init physics engine
		physicsEngine.Init();

		// init game objects
		InitGameObjects();
	}
		
	void InitGameObjects()
	{
		InitFloor();
		InitWalls();
		InitMovableObjects();
	}

	void InitFloor()
	{
		GameObject gameObject;
		gameObject.transform.position = glm::vec3(0.0f, 0.0f, 10.0f);
		gameObject.transform.scale = glm::vec3(40.0f, 0.0001f, 40.f);
		gameObject.SetRenderable(std::make_shared<Renderable>(&cubeMesh, shader, glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);

		PhysicObjectDesc physicObject;
		physicObject.type = PhysicObjectType::PARTICLE;
		physicObject.mass = 0.0f; // static object
		physicObject.isAffectedByGravity = false;

		MathGeom::Vector3 pointA = glm::vec3(1.0f, 0.0001f, 0.0f);
		MathGeom::Vector3 pointB = glm::vec3(-1.0f, 0.0001f, 0.0f);
		MathGeom::Vector3 pointC = glm::vec3(0.0f, 0.0001f, 0.5f);;
		physicObject.colliderDesc = std::make_unique<PlaneColliderDesc>(pointA, pointB, pointC, gameObjects.back().transform);

		physicsEngine.AddPhysics(gameObjects.back(), physicObject);
	}

	void InitWalls()
	{
		GameObject gameObject;
		gameObject.transform.position = glm::vec3(40.0f, 5.0f, 10.0f);
		gameObject.transform.scale = glm::vec3(0.5f, 5.0f, 40.f);
		gameObject.SetRenderable(std::make_shared<Renderable>(&cubeMesh, shader, glm::vec4(0.11f, 0.11f, 0.11f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);

		gameObject.transform.position = glm::vec3(-40.0f, 5.0f, 10.0f);
		gameObject.transform.scale = glm::vec3(0.5f, 5.0f, 40.f);
		gameObject.SetRenderable(std::make_shared<Renderable>(&cubeMesh, shader, glm::vec4(0.11f, 0.11f, 0.11f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);

		gameObject.transform.position = glm::vec3(0.0f, 5.0f, 50.0f);
		gameObject.transform.scale = glm::vec3(40.0f, 5.0f, 0.5f);
		gameObject.SetRenderable(std::make_shared<Renderable>(&cubeMesh, shader, glm::vec4(0.11f, 0.11f, 0.11f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);

		gameObject.transform.position = glm::vec3(0.0f, 5.0f, -30.0f);
		gameObject.transform.scale = glm::vec3(40.0f, 5.0f, 0.5f);
		gameObject.SetRenderable(std::make_shared<Renderable>(&cubeMesh, shader, glm::vec4(0.11f, 0.11f, 0.11f, 1.0f)));
		gameObject.SetVisible(true);

		gameObjects.emplace_back(gameObject);
	}

	void InitMovableObjects()
	{
		// green object
		GameObject greenObject;
		greenObject.transform.position = glm::vec3(-20.0f, 8.5f, 40.0f);
		greenObject.transform.scale = glm::vec3(2.0f, 2.0f, 2.0f);
		float sphereRadius = greenObject.transform.scale.x;
		//greenObject.SetRenderable(std::shared_ptr<Renderable>(static_cast<Renderable*>(new SphereRenderable(sphereRadius, &sphereMesh, shader, glm::vec4(0.0f, 0.3f, 0.0f, 1.0f)))));
		greenObject.SetRenderable(std::make_shared<Renderable>(&cubeMesh, shader, glm::vec4(0.0f, 0.3f, 0.0f, 1.0f)));
		greenObject.SetVisible(true);

		gameObjects.emplace_back(greenObject);

		PhysicObjectDesc greenPhysicObject;
		greenPhysicObject.type = PhysicObjectType::RIGID_BODY;
		greenPhysicObject.mass = 10.0f;
		greenPhysicObject.velocity = MathGeom::Vector3(0.6f, 0.0f, 0.0f);
		greenPhysicObject.acceleration = MathGeom::Vector3(0.6f, 0.0f, 0.0f);
		greenPhysicObject.angularVelocity = MathGeom::Vector3(0.0f, 1.0f, 0.0f);
		greenPhysicObject.inertiaTensor = PhysicsEngine::CuboidIntertiaTensor(greenPhysicObject.mass, gameObjects.back().transform.scale);
		//greenPhysicObject.inertiaTensor = PhysicsEngine::SphereIntertiaTensor(greenPhysicObject.mass, gameObjects.back().transform.scale.x);
		//greenPhysicObject.colliderDesc = std::make_unique<SphereColliderDesc>(gameObjects.back().transform);
		greenPhysicObject.colliderDesc = std::make_unique<AABBColliderDesc>(gameObjects.back().transform);
		greenPhysicObject.isAffectedByGravity = false;

		physicsEngine.AddPhysics(gameObjects.back(), greenPhysicObject);

		// red object
		GameObject redObject;
		redObject.transform.position = glm::vec3(25.0f, 5.5f, 40.0f);
		//redObject.transform.orientation = glm::angleAxis(glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		redObject.transform.scale = glm::vec3(3.0f, 3.0f, 3.0f);
		sphereRadius = redObject.transform.scale.x;
		//redObject.SetRenderable(std::shared_ptr<Renderable>(static_cast<Renderable*>(new SphereRenderable(sphereRadius, &sphereMesh, shader, glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)))));
		redObject.SetRenderable(std::make_shared<Renderable>(&cubeMesh, shader, glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)));
		redObject.SetVisible(true);

		gameObjects.emplace_back(redObject);

		PhysicObjectDesc redPhysicObject;
		redPhysicObject.type = PhysicObjectType::PARTICLE;
		redPhysicObject.mass = 10.0f;
		redPhysicObject.velocity = MathGeom::Vector3(-0.3f, 0.0f, 0.0f);
		redPhysicObject.acceleration = MathGeom::Vector3(-0.3f, 0.0f, 0.0f);
		redPhysicObject.inertiaTensor = PhysicsEngine::CuboidIntertiaTensor(redPhysicObject.mass, gameObjects.back().transform.scale);
		//redPhysicObject.inertiaTensor = PhysicsEngine::SphereIntertiaTensor(redPhysicObject.mass, gameObjects.back().transform.scale.x);
		//redPhysicObject.colliderDesc = std::make_unique<SphereColliderDesc>(gameObjects.back().transform);
		redPhysicObject.colliderDesc = std::make_unique<AABBColliderDesc>(gameObjects.back().transform);
		redPhysicObject.isAffectedByGravity = false;

		physicsEngine.AddPhysics(gameObjects.back(), redPhysicObject);
	}

	void Terminate()
	{
	}

private:
	
	// shader
	Shader shader;

	// cube mesh
	CubeMesh cubeMesh;

	// sphere mesh
	SphereMesh sphereMesh;

	// Camera
	FreeCamera camera;

	// game objects
	std::list<GameObject> gameObjects;

	// Physics engine
	PhysicsEngine physicsEngine;
};

#endif