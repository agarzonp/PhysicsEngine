#ifndef COLLISION_RESOLVER_H
#define COLLISION_RESOLVER_H

#include "ContactData.h"

class CollisionResolver
{
public:
	
	// Resolve
 	void Resolve(const ContactData& contact, float deltaTime)
	{
		assert(contact.objectA || contact.objectB); // No need to create a contact for 2 immovable objects

		// resolve velocity
		ResolveVelocity(contact, deltaTime);

		// resolve interpenetration
		ResolveInterpenetration(contact, deltaTime);
	}

private:

	// Resolve velocity
	void ResolveVelocity(const ContactData& contact, float deltaTime)
	{
		PhysicObject* objectA = contact.objectA;
		PhysicObject* objectB = contact.objectB;

		// check separating velocity
		float separatingVelocity = GetSeparatingVelocity(objectA, objectB, contact.normal);
		if (separatingVelocity > 0)
		{
			// objects already separating, no need to change the velocity
			return;
		}

		// new separating velocity
		float newSeparatingVelocity = -contact.restitution*separatingVelocity;
		float deltaVelocity = newSeparatingVelocity - separatingVelocity;
		
		// get impulse
		MathGeom::Vector3 impulse = GetImpulse(objectA, objectB, contact.normal, deltaVelocity);

		// Apply the impulse. In other words, change the velocity in proportion to the mass (impulse = mass * change_in_velocity)
		MathGeom::Vector3 velocityChange = impulse * objectA->InverseMass();
		objectA->Velocity() += velocityChange;
		if (objectB)
		{
			velocityChange = -impulse * objectB->InverseMass(); // negative because separating in opposite direction
			objectB->Velocity() += velocityChange;
		}
	}

	// Get separating velocity
	float GetSeparatingVelocity(PhysicObject* objectA, PhysicObject* objectB, const MathGeom::Vector3& contactNormal)
	{
		MathGeom::Vector3 velocity = objectA->Velocity();
		if (objectB)
		{
			// contact with not immovable object
			velocity -= objectB->Velocity();
		}

		return MathGeom::dot(velocity, contactNormal);
	}

	// Get Impulse
	MathGeom::Vector3 GetImpulse(PhysicObject* objectA, PhysicObject* objectB, const MathGeom::Vector3& contactNormal, float deltaVelocity)
	{
		float totalInverseMass = objectA->InverseMass();
		if (objectB)
		{
			totalInverseMass += objectB->InverseMass();
		}

		float impulseAmount = deltaVelocity / totalInverseMass;
		return contactNormal * impulseAmount;
	}

	// Resolve interpenetration
	void ResolveInterpenetration(const ContactData& contact, float deltaTime)
	{
		// TO-DO
	}

};

#endif // !COLLISION_RESOLVER_H

