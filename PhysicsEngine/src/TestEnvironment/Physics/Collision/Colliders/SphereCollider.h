#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include "Collider.h"

class SphereCollider : public Collider
{
public:

	// radius
	float radius{ 1.0f };

	// Constructor
	SphereCollider() = delete;
	SphereCollider(Transform& transform)
		: Collider(ColliderType::SPHERE, transform)
	{
		UpdateFromTransform();
	}

	// Debug Render
	void DebugRender(const glm::mat4& viewProjection) final
	{
		RenderUtils::RenderSphere(viewProjection, radius + 0.01f, transform, 0xFFFFFF);
	}

protected:

	// update from transform
	void UpdateFromTransform() final
	{
		radius = std::fmaxf(std::fmaxf(transform.scale.x, transform.scale.y), transform.scale.z);
	}
};

#endif // !SPHERE_COLLIDER_H

