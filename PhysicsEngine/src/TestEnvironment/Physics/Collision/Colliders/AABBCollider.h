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

	// Debug Render
	void DebugRender(const glm::mat4& viewProjection) final
	{
		Transform renderTransform = transform;
		renderTransform.scale.x = transform.scale.x * halfSize.x * 2.0f;
		renderTransform.scale.y = transform.scale.y * halfSize.y * 2.0f;
		renderTransform.scale.z = transform.scale.z * halfSize.z * 2.0f;

		RenderUtils::RenderCube(viewProjection, renderTransform, 0xFFFFFF);
	}
};

#endif // !AABB_COLLIDER_H
