#ifndef IPHYSIC_OBJECT_H
#define IPHYSIC_OBJECT_H

#include <vector>

#include "../Collision/Colliders/Collider.h"

class IPhysicObject
{
protected:

	// collider
	std::unique_ptr<Collider> collider;

public:

	// Add force
	virtual void AddForce(const MathGeom::Vector3& force) = 0;

	// Mass
	virtual float Mass() = 0;

	// Set collider
	void SetCollider(std::unique_ptr<Collider>& collider)
	{
		this->collider = std::move(collider);
	}

};

#endif // !IPHYSIC_OBJECT_H

