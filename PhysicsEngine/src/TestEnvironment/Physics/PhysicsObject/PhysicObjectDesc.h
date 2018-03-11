#ifndef PHYSIC_OBJECT_DESC_H
#define PHYSIC_OBJECT_DESC_H

enum class PhysicObjectType
{
	PARTICLE
};

struct PhysicObjectDesc
{
	PhysicObjectType type;

	float mass{ 0.0f };
	
	MathGeom::Vector3 position;
	MathGeom::Vector3 velocity;
	MathGeom::Vector3 acceleration;

	bool isAffectedByGravity{ true };
};

#endif // !PHYSIC_OBJECT_DESC_H

