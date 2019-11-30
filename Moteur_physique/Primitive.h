#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "RigidBody.h"
#include "Matrix4.h"
#include "Bounds.h"
class Primitive
{
private :
	RigidBody *body;
	Matrix4 offset;
	
public:
	Primitive();
	~Primitive();
	Bounds bounds_;
};
#endif
