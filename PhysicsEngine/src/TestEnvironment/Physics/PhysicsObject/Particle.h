#ifndef PARTICLE_H
#define PARTICLE_H

#include "PhysicObject.h"

class Particle : public PhysicObject
{
public:

	// Constructors
	Particle() = default;
	Particle(GameObject& object, const PhysicObjectDesc& desc)
		: PhysicObject(object, desc)
	{
	}

	// Integrate
	void Integrate(float deltaTime) final
	{
		if (inverseMass <= 0.0f)
		{
			// Do not integrate objects with infinite mass (static objects)
			return;
		}

		// integrate linear
		IntegrateLinear(deltaTime);
	}

};

#endif // !PARTICLE

