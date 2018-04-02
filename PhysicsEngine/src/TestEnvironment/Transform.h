#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "MathGeom.h"

struct Transform
{
	// position
	MathGeom::Vector3 position;

	// orientation
	MathGeom::Quaternion orientation;

	// scale
	MathGeom::Vector3 scale { 1.0f, 1.0f , 1.0f };

	// rotation matrix
	MathGeom::Matrix4 RotationMatrix4() const { return MathGeom::ToMatrix4(orientation); }
	MathGeom::Matrix3 RotationMatrix3() const { return MathGeom::ToMatrix3(orientation); }
};

#endif
