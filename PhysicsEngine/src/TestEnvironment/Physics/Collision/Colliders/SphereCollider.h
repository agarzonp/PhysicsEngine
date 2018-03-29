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
	SphereCollider(float radius_, Transform& transform)
		: Collider(ColliderType::SPHERE, transform)
		, radius(radius_)
	{
	}

	// Debug Render
	void DebugRender(const glm::mat4& viewProjection) final
	{
		RenderUtils::RenderSphere(viewProjection, radius + 0.01f, transform, 0xFFFFFF);
	}
};

#endif // !SPHERE_COLLIDER_H

