#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "RigidBody.h"
#include "Matrix4.h"
#include "Bounds.h"
class Primitive
{
private :
	RigidBody *body_;
	Matrix4 rotation;

	Vector3D pointRotationByQuaternion(Vector3D point, Quaternion q);
	bool pointIsWithinBox(Vector3D point, Vector3D* p);
	
public:
	Primitive(RigidBody* body, Bounds b);
	~Primitive();

	Bounds bounds_ = Bounds(0,0,0,0,0,0);

	Vector3D* rotatedRepere();
	bool hasCollision(Primitive* primitive);
};
#endif
