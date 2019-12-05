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
	Primitive(Bounds b);
	~Primitive();
	Bounds bounds_ = Bounds(0,0,0,0,0,0);
};
#endif
