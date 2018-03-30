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
		std::vector<ContactData> contacts;

		// Collision Detection
		// TO-DO: replace brute force approach by a broad phase collision detection using spatial partitioning techniques
		for (size_t i = 0; i < objects.size() - 1; i++)
		{
			for (size_t j = i + 1; j < objects.size(); j++)
			{
				// TO-DO: get contact data from collision detection
				if (collisionDetector.IsCollision(*objects[i], *objects[j]))
				{
					printf("Collision!\n");

					// Push contact data				
				}
			}
		}

		// Collision Resolution
		for (auto& contact : contacts)
		{
			collisionResolver.Resolve(contact, deltaTime);
		}

		contacts.clear();
	}
};

#endif // !COLLISION_MANAGER_H

