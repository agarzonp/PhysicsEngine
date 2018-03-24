#ifndef COLLIDER_DESC_H
#define	COLLIDER_DESC_H

// Collider desc
struct ColliderDesc
{
	ColliderType type{ ColliderType::INVALID };
	Transform transform;

	ColliderDesc(ColliderType colliderType, Transform transform_) 
		: type(colliderType)
		, transform(transform_)
	{
	}
};

// AABB collider desc
struct AABBColliderDesc : public ColliderDesc
{
	MathGeom::Vector3 halfSize;

	AABBColliderDesc(MathGeom::Vector3& halfSize_, Transform& transform)
		: ColliderDesc(ColliderType::AABB, transform)
		, halfSize(halfSize_)
	{
	}
};

// Sphere collider desc
struct SphereColliderDesc : public ColliderDesc
{
	float radius{ 1.0f };

	SphereColliderDesc(float radius_, Transform& transform)
		: ColliderDesc(ColliderType::SPHERE, transform)
		, radius(radius_)
	{
	}
};

#endif // !COLLIDER_DESC_H

