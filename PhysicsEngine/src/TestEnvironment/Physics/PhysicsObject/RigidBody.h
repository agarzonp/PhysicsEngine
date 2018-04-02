#ifndef RIGID_BODY_H
#define	RIGID_BODY_H

#include "PhysicObject.h"

class RigidBody : public PhysicObject
{
	// Orientation
	MathGeom::Quaternion orientation;

	// Angular velocity
	MathGeom::Vector3 angularVelocity;

	// Inverse inertia tensor(local space)
	MathGeom::Matrix3 inverseInertiaTensorLocal;

	// Accumulated torques
	MathGeom::Vector3 accumulatedTorques;

	// cached data
	struct CachedData
	{
		// transform from local to world
		MathGeom::Matrix4 localToWorld;

		// Inverse inertia tensor(world space)
		MathGeom::Matrix3 inverseInertiaTensorWorld;
	};
	CachedData cachedData;

public:

	// Constructors
	RigidBody() = default;
	RigidBody(GameObject& object, const PhysicObjectDesc& desc)
		: PhysicObject(object, desc)
		, orientation(object.transform.orientation)
		, angularVelocity(desc.angularVelocity)
	{
		inverseInertiaTensorLocal = MathGeom::Inverse(desc.inertiaTensor);

		UpdateCachedData();
	}

	// Set orientation
	void SetOrientation(const MathGeom::Quaternion& q)
	{
		orientation = q;

		// set the new orientation to the game object
		// If the game object has a physics object attached, the transform of the collider will be updated too
		// So we make sure that if the object orientation is not handled by the integrator, the collider is still updated correctly
		gameObject->SetOrientation(orientation);
	}


	// Integrate
	void Integrate(float deltaTime) final
	{
		if (inverseMass <= 0.0f)
		{
			// Do not integrate objects with infinite mass (static objects)
			return;
		}

		// integrate linear components
		IntegrateLinear(deltaTime);

		// integrate angular components
		IntegrateAngular(deltaTime);

		// reset accumulated forces and torques
		accumulatedForces = MathGeom::Vector3();

		// update cached data
		UpdateCachedData();
	}

protected:

	// Integrate angular
	void IntegrateAngular(float deltaTime)
	{
		// angular acceleration 
		MathGeom::Vector3 angularAcceleration = InverseInertiaTensor() * accumulatedTorques;
	
		// update angular velocity 
		angularVelocity+= angularAcceleration *deltaTime;

		// update angular position
		MathGeom::Quaternion angularVelocityQuaternion(0, angularVelocity*deltaTime);
		auto newOrientation = orientation + angularVelocityQuaternion * orientation;
		SetOrientation(newOrientation);

		// reset accumulated torques
		accumulatedTorques = MathGeom::Vector3();
	}

	// Inverse inertia tensor
	const MathGeom::Matrix3& InverseInertiaTensor() const { return cachedData.inverseInertiaTensorWorld; }

private:

	// Update cached data
	void UpdateCachedData()
	{
		// normalize orientation so we make sure that is valid for rotations
		orientation = glm::normalize(orientation);

		// update fromLocalToWorld transform
		cachedData.localToWorld = MathGeom::ToMatrix3(orientation);
		cachedData.localToWorld[3] = MathGeom::Vector4(position, 1.0f);

		// update inertia tensor in world space (change of basis transform  = Mb*Mt*inverse(Mb))
		// Note: the inverse of a rotation matrix is the transposeof the matrix
		MathGeom::Matrix3 localToWorldRot;
		localToWorldRot[0] = cachedData.localToWorld[0];
		localToWorldRot[1] = cachedData.localToWorld[1];
		localToWorldRot[2] = cachedData.localToWorld[2];
		cachedData.inverseInertiaTensorWorld = localToWorldRot * inverseInertiaTensorLocal * glm::transpose(localToWorldRot);
	}
};

#endif
