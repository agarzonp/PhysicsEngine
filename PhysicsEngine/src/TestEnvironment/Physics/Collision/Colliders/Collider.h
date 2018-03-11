#ifndef COLLIDER_H
#define COLLIDER_H

enum class ColliderType
{
	INVALID,
	SPHERE
};

class Collider
{
	// collider type
	ColliderType type{ ColliderType::INVALID };

public:

	// Transform
	Transform transform;

public:
	
	// Constructors
	Collider() = default;
	Collider(ColliderType colliderType, Transform& transform_) 
		: type(colliderType)
		, transform(transform_)
	{
	}

	// Destructor
	virtual ~Collider() {}

	// Get Type
	ColliderType GetType() const { return type; }

	// Set position
	void SetPosition(MathGeom::Vector3& pos) { transform.position = pos; }
};

#endif // !COLLIDER_H

