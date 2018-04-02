#ifndef MATH_GEOM_H
#define MATH_GEOM_H

#include "glm/glm.hpp"

namespace MathGeom
{
	using Vector2 = glm::vec2;
	using Vector3 = glm::vec3;
	using Vector4 = glm::vec4;

	using Matrix2 = glm::mat2;
	using Matrix3 = glm::mat3;
	using Matrix4 = glm::mat4;

	using Quaternion = glm::quat;

	const double PI = 3.14159265358979323846;

	// inverse
	template<class Matrix>
	Matrix Inverse(const Matrix& mat)
	{
		return glm::inverse(mat);
	}

	// To Matrix3 from a quaternion
	Matrix4 ToMatrix4(const Quaternion& q)
	{
		return glm::toMat4(q);
	}

	// To Matrix4 from a quaternion
	Matrix3 ToMatrix3(const Quaternion& q)
	{
		return glm::toMat3(q);
	}
	
	// Dot product
	float Dot(const Vector3& a, const Vector3& b)
	{
		return glm::dot(a, b);
	}

	// Distance squared
	float DistanceSq(const Vector3& a, const Vector3& b)
	{
		auto fromAtoB = b - a;
		return Dot(fromAtoB, fromAtoB);
	}

}


#endif // !MATH_H

