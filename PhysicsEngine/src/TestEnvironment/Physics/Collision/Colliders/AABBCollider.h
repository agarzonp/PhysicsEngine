#ifndef AABB_COLLIDER_H
#define AABB_COLLIDER_H

#include "Collider.h"

class AABBCollider : public Collider
{
public:

	// half size
	MathGeom::Vector3 halfSize;

	// Constructor
	AABBCollider() = delete;
	AABBCollider(MathGeom::Vector3& halfSize_, Transform& transform)
		: Collider(ColliderType::AABB, transform)
		, halfSize(halfSize_)
	{
	}
};

#endif // !AABB_COLLIDER_H
