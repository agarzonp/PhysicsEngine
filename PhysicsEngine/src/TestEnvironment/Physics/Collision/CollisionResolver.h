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
		float impulseAmount = deltaVelocity / GetTotalInverseMass(objectA, objectB);
		return contactNormal * impulseAmount;
	}

	// Get total inverse mass
	float GetTotalInverseMass(PhysicObject* objectA, PhysicObject* objectB)
	{
		float totalInverseMass = objectA->InverseMass();
		if (objectB)
		{
			totalInverseMass += objectB->InverseMass();
		}
		assert(totalInverseMass > 0);
		return totalInverseMass;
	}

	// Resolve interpenetration
	void ResolveInterpenetration(const ContactData& contact, float deltaTime)
	{
		float penetration = contact.penetration;
		if (penetration <= 0)
		{
			// no penetration at all
			return;
		}

		PhysicObject* objectA = contact.objectA;
		PhysicObject* objectB = contact.objectB;

		// calculate positional change and apply it to each object
		MathGeom::Vector3 displacement = contact.normal * (penetration / GetTotalInverseMass(objectA, objectB));
		MathGeom::Vector3 positionChange = displacement * objectA->InverseMass();
		objectA->SetPosition(objectA->Position() + positionChange);
		if (objectB)
		{
			positionChange = -displacement * objectB->InverseMass(); // negative because separating in opposite direction
			objectB->SetPosition(objectB->Position() + positionChange);
		}
	}

};

#endif // !COLLISION_RESOLVER_H

