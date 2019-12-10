#include "Primitive.h"

Primitive::Primitive(RigidBody* body, Bounds b)
{
	bounds_ = b;
	body_ = body;
}


Primitive::~Primitive()
{
}

Vector3D Primitive::pointRotationByQuaternion(Vector3D point, Quaternion q)
{
	Quaternion r{ 0, point.x, point.y, point.z };

	Quaternion q_conj{q.r_, -q.i_, -q.j_, -q.k_};

	Quaternion result = (q * r) * q_conj;

	return Vector3D(result.i_, result.j_, result.k_);
}

