#ifndef COLLISION_RESOLVER_H
#define COLLISION_RESOLVER_H

#include "ContactData.h"

class CollisionResolver
{
public:
	
	// Resolve
 	void Resolve(const ContactData& contact, float deltaTime)
	{
		// resolve velocity
		ResolveVelocity(contact, deltaTime);

		// resolve interpenetration
		ResolveInterpenetration(contact, deltaTime);
	}

private:

	// Resolve velocity
	void ResolveVelocity(const ContactData& contact, float deltaTime)
	{
		// TO-DO
	}

	// Resolve interpenetration
	void ResolveInterpenetration(const ContactData& contact, float deltaTime)
	{
		// TO-DO
	}

};

#endif // !COLLISION_RESOLVER_H

