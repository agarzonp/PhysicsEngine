#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

#include "../../GameObject.h"

#include "IPhysicObject.h"
#include "PhysicObjectDesc.h"


class PhysicObject : public IPhysicObject
{
	// game object
	GameObject* gameObject {nullptr};

	// mass
	float mass {0.0f};
	float inverseMass {0.0f};

	// position, velocity and acceleration
	MathGeom::Vector3 position;
	MathGeom::Vector3 velocity;
	MathGeom::Vector3 acceleration;
	
	// accumulated forces
	MathGeom::Vector3 accumulatedForces;

public:

	// Constructors
	PhysicObject() = default;
	PhysicObject(GameObject& gameObject_, const PhysicObjectDesc& desc)
		: gameObject(&gameObject_)
		, mass(desc.mass)
		, inverseMass(desc.mass > 0.0f ? 1.0f/desc.mass : 0.0f)
		, position(gameObject_.transform.position)
		, velocity(desc.velocity)
		, acceleration(desc.acceleration)
	{
	}

	// Add force
	void AddForce(const MathGeom::Vector3& force) final
	{
		accumulatedForces += force;
	}

	// Mass getter
	float Mass() final 
	{
		return mass;
	}

	// Has collider
	bool HasCollider() const { return collider != nullptr; }

	// Get collider
	const Collider& GetCollider() const { return *collider.get(); }

	// Integrate
	void Integrate(float deltaTime)
	{
		if (inverseMass <= 0.0f)
		{
			// Do not integrate objects with infinite mass (static objects)
			return;
		}

		// update velocity 
		velocity += (acceleration + accumulatedForces*inverseMass)*deltaTime;

		// update position
		position += velocity*deltaTime;

		// set the new position to the game object
		gameObject->SetPosition(position);

		// set the new position of the collider
		if (collider)
		{
			collider->SetPosition(position);
		}
		
		// reset accumulated forces
		accumulatedForces = MathGeom::Vector3();
	}

};

#endif // !PHYSIC_OBJECT_H

