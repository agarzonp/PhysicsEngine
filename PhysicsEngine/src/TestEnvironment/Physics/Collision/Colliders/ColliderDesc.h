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

// Plane collider desc
struct PlaneColliderDesc : public ColliderDesc
{
	MathGeom::Vector3 pointA;
	MathGeom::Vector3 pointB;
	MathGeom::Vector3 pointC;

	PlaneColliderDesc(MathGeom::Vector3& a, MathGeom::Vector3& b, MathGeom::Vector3& c, Transform& transform)
		: ColliderDesc(ColliderType::PLANE, transform)
		, pointA(a)
		, pointB(b)
		, pointC(c)
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

