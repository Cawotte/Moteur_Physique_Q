#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "RigidBody.h"
#include "Matrix4.h"
#include "Bounds.h"

class Cube;
class Wall;

class Primitive {

protected :

	RigidBody* body_ = NULL;


	Primitive(RigidBody* body, Bounds b);
	Primitive() {};

	Vector3D pointRotationByQuaternion(Vector3D point, Quaternion q);

public:

	Bounds bounds_;
	Bounds originalBounds_;

	~Primitive();
	
	virtual bool isPrimitiveCollidingWith(Primitive* prim) = 0;
	virtual bool isPrimitiveCollidingWith(Cube* prim) = 0;
	virtual bool isPrimitiveCollidingWith(Wall* prim) = 0;

	void setBounds(Bounds b) { bounds_ = b; }

	void setOriginalBounds(Bounds b) { originalBounds_ = b; }

	void updateBounds();

	RigidBody* getBody() { return body_; }

};

#endif
