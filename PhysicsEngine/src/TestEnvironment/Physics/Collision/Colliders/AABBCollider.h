#ifndef AABB_COLLIDER_H
#define AABB_COLLIDER_H

#include "Collider.h"

class AABBCollider : public Collider
{
public:

	// half size
	MathGeom::Vector3 halfSize;

	// min and max
	MathGeom::Vector3 min;
	MathGeom::Vector3 max;

	// Constructor
	AABBCollider() = delete;
	AABBCollider(MathGeom::Vector3& halfSize_, Transform& transform)
		: Collider(ColliderType::AABB, transform)
		, halfSize(halfSize_)
	{
		min = transform.position - halfSize;
		max = transform.position + halfSize;
	}
};

#endif // !AABB_COLLIDER_H
