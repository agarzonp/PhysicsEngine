#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

#include "../../GameObject.h"

#include "IPhysicObject.h"
#include "PhysicObjectDesc.h"


class PhysicObject : public IPhysicObject
{
protected:

	// game object
	GameObject* gameObject {nullptr};
	Transform transform;

	// mass
	float mass {0.0f};
	float inverseMass {0.0f};

	// linear velocity and acceleration
	MathGeom::Vector3 velocity;
	MathGeom::Vector3 acceleration;
	
	// accumulated forces
	MathGeom::Vector3 accumulatedForces;

	// collider
	std::unique_ptr<Collider> collider;

public:

	// Constructors
	PhysicObject() = default;
	PhysicObject(GameObject& gameObject_, const PhysicObjectDesc& desc)
		: gameObject(&gameObject_)
		, transform(gameObject->transform)
		, mass(desc.mass)
		, inverseMass(desc.mass > 0.0f ? 1.0f/desc.mass : 0.0f)
		, velocity(desc.velocity)
		, acceleration(desc.acceleration)
	{
	}

	// Integrate
	virtual void Integrate(float deltaTime) = 0;

	// Add force
	void AddForce(const MathGeom::Vector3& force) override
	{
		accumulatedForces += force;
	}

	// Mass getter
	float Mass() final { return mass; }
	float InverseMass() const { return inverseMass; }

	// Set transform
	void SetTransform(const Transform& transform) final
	{
		this->transform = transform;

		SyncColliderTransform();
	}

	// Set collider
	void SetCollider(std::unique_ptr<Collider>& collider) final
	{
		this->collider = std::move(collider);
	}

	// Has collider
	bool HasCollider() const { return collider != nullptr; }

	// Get collider
	const Collider& GetCollider() const { return *collider.get(); }

	// Velocity getter/setter
	const MathGeom::Vector3& Velocity() const { return velocity; }
	MathGeom::Vector3& Velocity() { return velocity; }

	// Position getter/setter
	const MathGeom::Vector3& Position() const { return transform.position; }
	void SetPosition(const MathGeom::Vector3& pos)
	{
		transform.position = pos;

		SyncColliderTransform();
	}

	// Debg render collider
	void DebugRenderCollider(const glm::mat4& viewProjection)
	{
		if (collider)
		{
			collider->DebugRender(viewProjection);
		}
	}

protected:

	// Integrate linear components
	void IntegrateLinear(float deltaTime)
	{
		assert(inverseMass > 0.0f);

		// update acceleration by applying forces
		MathGeom::Vector3 finalAcceleration = acceleration;
		finalAcceleration += accumulatedForces*inverseMass;

		// update linear velocity 
		velocity += finalAcceleration*deltaTime;

		// update linear position
		transform.position += velocity*deltaTime;
		
		// reset accumulated forces
		accumulatedForces = MathGeom::Vector3();
	}

	// sync transform
	void SyncTransform()
	{
		// set the transform to the game object
		gameObject->SetTransform(transform);

		// set the transform to the collider
		SyncColliderTransform();
	}

	// sync collider transform
	void SyncColliderTransform()
	{
		if (collider)
		{
			collider->SetTransform(transform);
		}
	}
};

using PhysicObjects = std::vector<PhysicObject*>;

#endif // !PHYSIC_OBJECT_H

