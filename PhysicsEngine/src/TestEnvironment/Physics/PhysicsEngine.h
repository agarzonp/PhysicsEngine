#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>

#include "../GameObject.h"

#include "Collision/CollisionDetector.h"
#include "Forces/Forces.h"
#include "PhysicsObject/PhysicObjectDesc.h"
#include "PhysicsObject/Particle.h"

class PhysicsEngine
{
	// physic objects
	using PhysicObjects = std::vector<PhysicObject*>;
	PhysicObjects physicObjects;

	// particles
	using Particles = std::vector<Particle>;
	Particles particles;

	// forces map
	using ForcesMapEntryFirst = PhysicObject*;
	using ForcesMapEntrySecond = std::vector<std::unique_ptr<IForce>>;
	using ForcesMap = std::map<ForcesMapEntryFirst, ForcesMapEntrySecond>;
	ForcesMap forcesMap;

	// Collision detector
	CollisionDetector collisionDetector;

public:

	// Add physic to the game object
	IPhysicObject* AddPhysics(GameObject& object, const PhysicObjectDesc& desc)
	{
		switch (desc.type)
		{
			case PhysicObjectType::PARTICLE:
			{
				particles.emplace_back(Particle(object, desc));
				physicObjects.emplace_back(&particles.back());
				break;
			}
			default:
			{
				printf("PhysicObjectType (%d) not handled", (int)desc.type);
				return nullptr;
			}
		}

		// add gravity force
		auto forcesMapEntry = forcesMap.find(physicObjects.back());
		if (forcesMapEntry == forcesMap.end())
		{
			forcesMap.insert(std::pair<ForcesMapEntryFirst, ForcesMapEntrySecond>(physicObjects.back(), ForcesMapEntrySecond()));
			forcesMapEntry = forcesMap.find(physicObjects.back());
		}
		
		forcesMapEntry->second.emplace_back(std::make_unique<GravityForce>(MathGeom::Vector3(0.0f, -9.8f, 0.0f)));
		

		return physicObjects.back();
	}

	// Update
	void Update(float deltaTime)
	{
		// add forces
		AddForces();
		
		// integrate
		Integrate(deltaTime);

		// handle collision
		HandleCollisions();
	}

private:

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

	// Handle collisions
	void HandleCollisions()
	{
		// TO-DO: replace brute force approach by a broad phase collision detection using spatial partitioning techniques
		for (size_t i = 0; i < physicObjects.size() - 1; i++)
		{
			for (size_t j = i + 1; j < physicObjects.size(); j++)
			{
				if (collisionDetector.IsCollision(*physicObjects[i], *physicObjects[j]))
				{
					printf("Collision!");
				}
			}
		}
	}


};

#endif // !PHYSICS_ENGINE

