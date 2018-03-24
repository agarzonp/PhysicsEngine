#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "../PhysicsObject/PhysicObject.h"
#include "Colliders/Collider.h"
#include "CollisionTest.h"

class CollisionDetector
{
public:

	// IsCollision
	bool IsCollision(const PhysicObject& objectA, const PhysicObject& objectB)
	{
		if (!objectA.HasCollider() || !objectB.HasCollider())
		{
			return false;
		}

		// Test collision between colliders
		const Collider& colliderA = objectA.GetCollider();
		const Collider& colliderB = objectB.GetCollider();

		return Test(colliderA, colliderB);
	}

private:

	// Test collision
	bool Test(const Collider& colliderA, const Collider& colliderB)
	{
		switch (GetCollisionTestType(colliderA, colliderB))
		{
		case CollisionTest::Type::SPHERE_SPHERE:
			return CollisionTest::Sphere_Shere(colliderA, colliderB);
		case CollisionTest::Type::AABB_AABB:
			return CollisionTest::AABB_AABB(colliderA, colliderB);
		default:
			assert(false);
			break;
		}

		return false;
	}

	// Get collision test
	CollisionTest::Type GetCollisionTestType(const Collider& colliderA, const Collider& colliderB)
	{
		CollisionTest::Type testType = CollisionTest::Type::NONE;

		ColliderType colliderTypeA = colliderA.GetType();
		ColliderType colliderTypeB = colliderB.GetType();

		switch (colliderTypeA)
		{
			case ColliderType::AABB:
			{
				switch (colliderTypeB)
				{
				case ColliderType::AABB:
				{
					testType = CollisionTest::Type::AABB_AABB;
					break;
				}
				default:
					assert(false);
					break;
				}
				break;
			}
			case ColliderType::SPHERE:
			{
				switch (colliderTypeB)
				{
				case ColliderType::SPHERE:
				{
					testType = CollisionTest::Type::SPHERE_SPHERE;
					break;
				}
				default:
					assert(false);
					break;
				}
				break;
			}
			
			default:
			assert(false);
			break;
		}

		return testType;
	}
};
#endif // !COLLISION_DETECTOR_H

