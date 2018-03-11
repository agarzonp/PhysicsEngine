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
	
	// Constructors
	Collider() = default;
	Collider(ColliderType& colliderType) : type(colliderType) {}

	// Destructor
	virtual ~Collider() {}

	// Get Type
	ColliderType GetType() const { return type; }
};

#endif // !COLLIDER_H

