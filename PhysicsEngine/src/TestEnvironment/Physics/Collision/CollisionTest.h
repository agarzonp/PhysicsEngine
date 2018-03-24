#ifndef COLLISION_TEST_H
#define COLLISION_TEST_H

#include "Colliders/Collider.h"

#include "Colliders/AABBCollider.h"
#include "Colliders/SphereCollider.h"

class CollisionTest
{
public:

	enum class Type
	{
		NONE,
		AABB_AABB,
		SPHERE_SPHERE,
	};

	static bool AABB_AABB(const Collider& colliderA, const Collider& colliderB)
	{
		const AABBCollider& boxA = *static_cast<const AABBCollider*>(&colliderA);
		const AABBCollider& boxB = *static_cast<const AABBCollider*>(&colliderB);

		// check overlap in all the axes
		if (std::fabsf(boxA.transform.position.x - boxB.transform.position.x) > std::fabsf(boxA.halfSize.x + boxB.halfSize.x)) 
			return false;
		if (std::fabsf(boxA.transform.position.y - boxB.transform.position.y) > std::fabsf(boxA.halfSize.y + boxB.halfSize.y)) 
			return false;
		if (std::fabsf(boxA.transform.position.z - boxB.transform.position.z) > std::fabsf(boxA.halfSize.z + boxB.halfSize.z)) 
			return false;

		// overlap in all the axes
		return true;
	}

	static bool Sphere_Shere(const Collider& colliderA, const Collider& colliderB)
	{
		const SphereCollider& sphereA = *static_cast<const SphereCollider*>(&colliderA); 
		const SphereCollider& sphereB = *static_cast<const SphereCollider*>(&colliderB);
		
		// squared distance between centers by using the dot product
		auto fromAtoB = sphereA.transform.position - sphereB.transform.position;
		float distanceSq = glm::dot(fromAtoB, fromAtoB);

		float radiusSum = sphereA.radius + sphereB.radius;
		return distanceSq <= radiusSum * radiusSum;
	}
};

#endif // !COLLISION_TEST_H

