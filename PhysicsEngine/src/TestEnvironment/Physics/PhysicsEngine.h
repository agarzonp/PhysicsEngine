#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>

#include "../GameObject.h"
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

		return physicObjects.back();
	}

	// Integrate each physic object
	void Integrate(float deltaTime)
	{
		for (auto physicObject : physicObjects)
		{
			physicObject->Integrate(deltaTime);
		}
	}


};

#endif // !PHYSICS_ENGINE

