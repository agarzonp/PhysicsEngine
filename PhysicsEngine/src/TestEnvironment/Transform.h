#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "MathGeom.h"

struct Transform
{
	MathGeom::Vector3 position;
	MathGeom::Vector3 rotation;
	MathGeom::Vector3 scale;
};

#endif
