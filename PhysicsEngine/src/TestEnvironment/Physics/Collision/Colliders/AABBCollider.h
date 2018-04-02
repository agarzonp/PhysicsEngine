#ifndef AABB_COLLIDER_H
#define AABB_COLLIDER_H

#include <array>

#include "Collider.h"

class AABBCollider : public Collider
{
public:

	// half size
	MathGeom::Vector3 halfSize;

	// half size offset
	MathGeom::Vector3 halfSizeOffset;

	// vertices
	std::array<MathGeom::Vector3, 8> vertices;

	// Constructor
	AABBCollider() = delete;
	AABBCollider(Transform& transform)
		: Collider(ColliderType::AABB, transform)
	{
		UpdateFromTransform();
	}
	
	// Get vertices
	std::array<MathGeom::Vector3, 8> Vertices() const
	{
		auto& center = transform.position;

		std::array<MathGeom::Vector3, 8> vertices;
		vertices[0] = { center.x + halfSize.x + halfSizeOffset.x, center.y + halfSize.y + halfSizeOffset.y, center.z + halfSize.z + halfSizeOffset.z };
		vertices[1] = { center.x + halfSize.x + halfSizeOffset.x, center.y - halfSize.y - halfSizeOffset.y, center.z + halfSize.z + halfSizeOffset.z };
		vertices[2] = { center.x - halfSize.x - halfSizeOffset.x, center.y - halfSize.y - halfSizeOffset.y, center.z + halfSize.z + halfSizeOffset.z };
		vertices[3] = { center.x - halfSize.x - halfSizeOffset.x, center.y + halfSize.y + halfSizeOffset.y, center.z + halfSize.z + halfSizeOffset.z };
		vertices[4] = { center.x + halfSize.x + halfSizeOffset.x, center.y + halfSize.y + halfSizeOffset.y, center.z - halfSize.z - halfSizeOffset.z };
		vertices[5] = { center.x + halfSize.x + halfSizeOffset.x, center.y - halfSize.y - halfSizeOffset.y, center.z - halfSize.z - halfSizeOffset.z };
		vertices[6] = { center.x - halfSize.x - halfSizeOffset.x, center.y - halfSize.y - halfSizeOffset.y, center.z - halfSize.z - halfSizeOffset.z };
		vertices[7] = { center.x - halfSize.x - halfSizeOffset.x, center.y + halfSize.y + halfSizeOffset.y, center.z - halfSize.z - halfSizeOffset.z };
		return vertices;
	}

	// Debug Render
	void DebugRender(const glm::mat4& viewProjection) final
	{
		Transform AABBTransform;
		AABBTransform.position = transform.position;
		AABBTransform.scale = (halfSize + halfSizeOffset) * 1.001f;

		RenderUtils::RenderCube(viewProjection, AABBTransform, 0xFFFFFF);
	}

protected:

	// update from transform
	void UpdateFromTransform() final
	{
		if (halfSize != transform.scale)
		{
			halfSize = transform.scale;
			ComputeLocalVertices();
		}

		// rotate local vertices
		auto& rotation = MathGeom::ToMatrix3(transform.orientation);
		MathGeom::Vector3 max = vertices[0];
		for (auto vertex : vertices)
		{
			vertex = vertex * rotation;

			max.x = std::fmaxf(max.x, vertex.x);
			max.y = std::fmaxf(max.y, vertex.y);
			max.z = std::fmaxf(max.z, vertex.z);
		}

		// get halfSize extension
		halfSizeOffset = max - halfSize;
	}

	void ComputeLocalVertices()
	{
		// vertices in local coordinates
		vertices[0] = { halfSize.x,  halfSize.y,  halfSize.z };
		vertices[1] = { halfSize.x, -halfSize.y,  halfSize.z };
		vertices[2] = { -halfSize.x, -halfSize.y,  halfSize.z };
		vertices[3] = { -halfSize.x,  halfSize.y,  halfSize.z };
		vertices[4] = { halfSize.x,  halfSize.y, -halfSize.z };
		vertices[5] = { halfSize.x, -halfSize.y, -halfSize.z };
		vertices[6] = { -halfSize.x, -halfSize.y, -halfSize.z };
		vertices[7] = { -halfSize.x,  halfSize.y, -halfSize.z };
	}
};

#endif // !AABB_COLLIDER_H
