#ifndef PHYSIC_OBJECT_DESC_H
#define PHYSIC_OBJECT_DESC_H

#include "../Collision/Colliders/ColliderDesc.h"

enum class PhysicObjectType
{
	PARTICLE,
	RIGID_BODY
};

struct PhysicObjectDesc
{
	// type
	PhysicObjectType type;

	// mass
	float mass{ 0.0f };
	
	// linear velocity, acceleration
	MathGeom::Vector3 velocity;
	MathGeom::Vector3 acceleration;

	// angular velocity (only for rigid body)
	MathGeom::Vector3 angularVelocity;

	// inertia tensor (only for rigid body)
	MathGeom::Matrix3 inertiaTensor;

	// collider
	std::unique_ptr<ColliderDesc> colliderDesc;

	// hack to enable/disable gravity force on this object
	bool isAffectedByGravity{ true };
};

#endif // !PHYSIC_OBJECT_DESC_H

