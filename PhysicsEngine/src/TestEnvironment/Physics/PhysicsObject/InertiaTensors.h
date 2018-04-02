#ifndef INERTIA_TENSORS_H
#define INERTIA_TENSORS_H

#include "../../MathGeom.h"

class InertiaTensors
{
public:
	
	static MathGeom::Matrix3 Cuboid(float mass, const MathGeom::Vector3& extent)
	{
		MathGeom::Matrix3 inertiaTensor;

		float dx = extent.x * extent.x;
		float dy = extent.y * extent.y;
		float dz = extent.z * extent.z;

		float m = 0.1f/12.0f*mass;

		inertiaTensor[0] = { m*(dy + dz), 0.0f, 0.0f };
		inertiaTensor[1] = { 0.0f, m*(dx + dz), 0.0f };
		inertiaTensor[2] = { 0.0f, 0.0f, m*(dx + dy) };

		return inertiaTensor;
	}

	static MathGeom::Matrix3 Sphere(float mass, float radius)
	{
		MathGeom::Matrix3 inertiaTensor;

		float i = 0.4f * mass * radius * radius;

		inertiaTensor[0] = { i, 0.0f, 0.0f };
		inertiaTensor[1] = { 0.0f, i, 0.0f };
		inertiaTensor[2] = { 0.0f, 0.0f, i };

		return inertiaTensor;
	}
};

#endif // !INERTIA_TENSORS_H

