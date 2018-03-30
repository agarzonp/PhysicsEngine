#ifndef CONTACT_DATA_H
#define CONTACT_DATA_H

#include <vector>

#include "../PhysicsObject/PhysicObject.h"

struct ContactData
{
	// pair of objects in contact
	PhysicObject* objectA{ nullptr };
	PhysicObject* objectB{ nullptr }; // it could be null for immovable objects

	// contact normal (from objectA perspective)
	MathGeom::Vector3 normal;

	// coefficient of restitution (the speed at which the objects will separate after colliding)
	float restitution;

	// depth of penetration in the direction of the contact normal
	float penetration;
};

using Contacts = std::vector<ContactData>;

#endif
