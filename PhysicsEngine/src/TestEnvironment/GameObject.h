#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "CubeRenderable.h"
#include "MathGeom.h"

struct Transform_
{
	MathGeom::Vector3 position;
	MathGeom::Vector3 rotation;
	MathGeom::Vector3 scale;
};

class GameObject
{
	Transform_ transform;
	CubeRenderable renderable;

public:

	GameObject() {};

	const Transform_& Transform() const { return transform; }
	Transform_& Transform() { return transform; }

	void SetPosition(MathGeom::Vector3& pos) {transform.position = pos; }

	const CubeRenderable& GetRenderable() const { return renderable; }
	void SetRenderable(const CubeRenderable& renderable_) { renderable = renderable_; }
	
	void SetVisible(bool visible) { renderable.SetVisible(visible); }
	bool IsVisible() { return renderable.IsVisible(); }
};

#endif // !GAME_OBJECT_H


