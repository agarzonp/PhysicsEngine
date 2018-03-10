#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Render/Renderable.h"
#include "MathGeom.h"

#include "Physics/PhysicsObject/IPhysicObject.h"

#include "Transform.h"

class GameObject
{
	// physic object
	IPhysicObject* physicObject{ nullptr };

	// renderable
	Renderable renderable;

public:

	// Transform
	Transform transform;

public:

	// Set position
	void SetPosition(MathGeom::Vector3& pos) {transform.position = pos; }

	// Set renderable
	void SetRenderable(const Renderable& renderable_) { renderable = renderable_; }

	// Set visible
	void SetVisible(bool visible) { renderable.SetVisible(visible); }

	// Set physics object
	void SetPhysicObject(IPhysicObject* physicsObj) { physicObject = physicsObj; }

	// Render
	void Render(const glm::mat4& viewProjection)
	{
		renderable.Render(viewProjection, transform);
	}
};

#endif // !GAME_OBJECT_H


