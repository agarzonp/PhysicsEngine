#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

#include "../../GameObject.h"

#include "PhysicObjectDesc.h"


class PhysicObject
{
	GameObject* gameObject {nullptr};

	float mass {0.0f};
	MathGeom::Vector3 position;
	MathGeom::Vector3 velocity;
	MathGeom::Vector3 acceleration;

public:

	PhysicObject() = default;
	PhysicObject(GameObject& gameObject_, const PhysicObjectDesc& desc)
		: gameObject(&gameObject_)
		, mass(desc.mass)
		, position(gameObject_.Transform().position)
		, velocity(desc.velocity)
		, acceleration(desc.acceleration)
	{
	}

	void Integrate(float deltaTime)
	{
		// update velocity and position
		velocity += acceleration*deltaTime;
		position += velocity*deltaTime;

		// set the new position to the game object
		gameObject->SetPosition(position);
	}

};

#endif // !PHYSIC_OBJECT_H

