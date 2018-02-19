#ifndef IPHYSIC_OBJECT_H
#define IPHYSIC_OBJECT_H

class IPhysicObject
{
public:
	virtual void AddForce(const MathGeom::Vector3& force) = 0;
	virtual float Mass() = 0;
};

#endif // !IPHYSIC_OBJECT_H

