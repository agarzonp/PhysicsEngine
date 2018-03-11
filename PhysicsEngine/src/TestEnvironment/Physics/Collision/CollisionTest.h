#ifndef COLLISION_TEST_H
#define COLLISION_TEST_H

#include "Colliders/Collider.h"
#include "Colliders/SphereCollider.h"

class CollisionTest
{
public:

	enum class Type
	{
		NONE,
		SPHERE_SPHERE
	};

	static bool TestSphereShere(const SphereCollider& sphereA, const SphereCollider& sphereB)
	{
		// TO-DO
		return false;
	}
};

#endif // !COLLISION_TEST_H

