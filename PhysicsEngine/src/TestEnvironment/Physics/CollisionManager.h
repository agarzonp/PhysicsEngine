#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "PhysicsObject/PhysicObject.h"

#include "Collision/ContactData.h"
#include "Collision/CollisionDetector.h"
#include "Collision/CollisionResolver.h"

class CollisionManager
{
	// Collision detector
	CollisionDetector collisionDetector;

	// Collision resolver
	CollisionResolver collisionResolver;

public:

	void Update(PhysicObjects& objects, float deltaTime)
	{
		Contacts contacts;

		// Collision Detection
		// TO-DO: replace brute force approach by a broad phase collision detection using spatial partitioning techniques
		for (size_t i = 0; i < objects.size() - 1; i++)
		{
			for (size_t j = i + 1; j < objects.size(); j++)
			{
				ContactData contact;
				if (collisionDetector.IsCollision(*objects[i], *objects[j], contact))
				{
					printf("Collision!\n");
					assert(contact.objectA);

					contacts.emplace_back(contact);
				}
			}
		}

		// Collision Resolution
		collisionResolver.Resolve(contacts, deltaTime);
	}
};

#endif // !COLLISION_MANAGER_H

