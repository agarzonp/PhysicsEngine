#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>

#include "../GameObject.h"

#include "Forces/Forces.h"
#include "PhysicsObject/InertiaTensors.h"
#include "PhysicsObject/PhysicObjectDesc.h"
#include "PhysicsObject/Particle.h"
#include "PhysicsObject/RigidBody.h"

#include "CollisionManager.h"

class PhysicsEngine
{
	// physic objects
	PhysicObjects physicObjects;

	// particles
	static const int MAX_PARTICLE_OBJECTS = 100;
	using Particles = std::vector<Particle>;
	Particles particles;

	// rigid bodies
	static const int MAX_RIGID_BODY_OBJECTS = 100;
	using RigidBodies = std::vector<RigidBody>;
	RigidBodies rigidBodies;

	// forces map
	using ForcesMapEntryFirst = PhysicObject*;
	using ForcesMapEntrySecond = std::vector<std::unique_ptr<IForce>>;
	using ForcesMap = std::map<ForcesMapEntryFirst, ForcesMapEntrySecond>;
	ForcesMap forcesMap;

	// Collision manager
	CollisionManager collisionManager;

public:

	// Init
	void Init()
	{
		particles.reserve(MAX_PARTICLE_OBJECTS);
		
		size_t maxContacts = 500;
		collisionManager.Init(maxContacts);
	}

	// Add physic to the game object
	IPhysicObject* AddPhysics(GameObject& object, const PhysicObjectDesc& desc)
	{
		// create physic object
		PhysicObject* physicObject = CreatePhysicObject(object, desc);
		if (!physicObject)
		{
			return nullptr;
		}

		// set collider
		SetCollider(physicObject, desc.colliderDesc);

		// register gravity force
		if (desc.isAffectedByGravity)
		{
			std::unique_ptr<IForce> gravityForce = std::make_unique<GravityForce>(MathGeom::Vector3(0.0f, -9.8f, 0.0f));
			RegisterForce(physicObject, gravityForce);
		}
		
		// attach the physics object to the game object
		object.SetPhysicObject(physicObject);

		return physicObject;
	}

	// Update
	void Update(float deltaTime)
	{
		if (physicObjects.size() == 0)
		{
			// nothing to update
			return;
		}

		// add forces
		AddForces();
		
		// integrate
		Integrate(deltaTime);

		// handle collision
		collisionManager.Update(physicObjects, deltaTime);
	}

	// Debug render
	void DebugRender(const glm::mat4& viewProjection)
	{
		// debug render colliders
		DebugRenderColliders(viewProjection);
	}

private:

	// Create Physic Object
	PhysicObject* CreatePhysicObject(GameObject& object, const PhysicObjectDesc& desc)
	{
		PhysicObject* physicObject = nullptr;

		switch (desc.type)
		{
		case PhysicObjectType::PARTICLE:
		{
			assert(particles.size() < MAX_PARTICLE_OBJECTS);
			if (particles.size() < MAX_PARTICLE_OBJECTS)
			{
				particles.emplace_back(object, desc);
				physicObjects.emplace_back(&particles.back());
				physicObject = physicObjects.back();
			}
			break;
		}

		case PhysicObjectType::RIGID_BODY:
		{
			assert(rigidBodies.size() < MAX_RIGID_BODY_OBJECTS);
			if (rigidBodies.size() < MAX_RIGID_BODY_OBJECTS)
			{
				rigidBodies.emplace_back(object, desc);
				physicObjects.emplace_back(&rigidBodies.back());
				physicObject = physicObjects.back();
			}
			break;
		}
		default:
			printf("PhysicObjectType (%d) not handled", (int)desc.type);
			break;
		}

		return physicObject;
	}

	// Set collider
	void SetCollider(PhysicObject* physicObject, const std::unique_ptr<ColliderDesc>& colliderDesc)
	{
		assert(colliderDesc);
		if (colliderDesc)
		{
			std::unique_ptr<Collider> collider;

			switch (colliderDesc->type)
			{
			case ColliderType::AABB:
			{
				collider = std::make_unique<AABBCollider>(colliderDesc->transform);
				break;
			}
			case ColliderType::PLANE:
			{
				MathGeom::Vector3 pointA = static_cast<PlaneColliderDesc*>(colliderDesc.get())->pointA;
				MathGeom::Vector3 pointB = static_cast<PlaneColliderDesc*>(colliderDesc.get())->pointB;
				MathGeom::Vector3 pointC = static_cast<PlaneColliderDesc*>(colliderDesc.get())->pointC;

				collider = std::make_unique<PlaneCollider>(pointA, pointB, pointC, colliderDesc->transform);

				break;
			}
			case ColliderType::SPHERE:
			{
				collider = std::make_unique<SphereCollider>(colliderDesc->transform);
				break;
			}
			default:
				assert(false);
				break;
			}

			physicObject->SetCollider(collider);
		}
	}

	// Register force
	void RegisterForce(PhysicObject* physicObject, std::unique_ptr<IForce>& force)
	{
		auto forcesMapEntry = forcesMap.find(physicObject);
		if (forcesMapEntry == forcesMap.end())
		{
			forcesMap.insert(std::pair<ForcesMapEntryFirst, ForcesMapEntrySecond>(physicObject, ForcesMapEntrySecond()));
			forcesMapEntry = forcesMap.find(physicObject);
		}

		forcesMapEntry->second.emplace_back(std::move(force));
	}

	// Add forces
	void AddForces()
	{
		for (auto& forceEntry : forcesMap)
		{
			PhysicObject& physicObject = *forceEntry.first;
			for (auto& force : forceEntry.second)
			{
				force->AddTo(physicObject);
			}
		}
	}

	// Integrate each physic object
	void Integrate(float deltaTime)
	{
		for (auto physicObject : physicObjects)
		{
			physicObject->Integrate(deltaTime);
		}
	}
	
public:

	static MathGeom::Matrix3 CuboidIntertiaTensor(float mass, const MathGeom::Vector3& extent)
	{
		return InertiaTensors::Cuboid(mass, extent);
	}

	static MathGeom::Matrix3 SphereIntertiaTensor(float mass, float radius)
	{
		return InertiaTensors::Sphere(mass, radius);
	}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// DEBUG
public:

	static bool s_renderColliders;

private:

	// Render colliders
	void DebugRenderColliders(const MathGeom::Matrix4& viewProjection)
	{
		if (s_renderColliders)
		{
			for (size_t i = 0; i < physicObjects.size(); i++)
			{
				physicObjects[i]->DebugRenderCollider(viewProjection);
			}
		}
	}

// DEBUG
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

};

bool PhysicsEngine::s_renderColliders = false;

#endif // !PHYSICS_ENGINE

