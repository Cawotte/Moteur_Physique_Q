#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "RigidBody.h"
#include "Matrix4.h"
#include "Bounds.h"

class Primitive {

private :

	RigidBody* body_ = NULL;
	Matrix4 rotation;

public:

	Bounds bounds_;

	Primitive(RigidBody* body, Bounds b);
	Primitive() {};
	~Primitive();

	Vector3D pointRotationByQuaternion(Vector3D point, Quaternion q);
	bool pointIsWithinBox(Vector3D point, Vector3D* p);
	Vector3D* rotatedRepere();

	void setBounds(Bounds b) { bounds_ = b; }
};

#endif
