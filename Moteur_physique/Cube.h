#ifndef CUBE_H
#define CUBE_H

#include "Primitive.h"
#include "Wall.h"

class Cube :
	public Primitive
{

private:

	bool isPointWithinCube(Vector3D point, Vector3D* rotatedRepere);

	Vector3D rotatePointWithOrientation(Vector3D point);

	Vector3D* rotatedRepere();
	bool arePointsCollidingWithPrimitive(Vector3D* points, int sizeArray);

public:

	Cube(RigidBody* body, Bounds b) : Primitive(body, b) {
	}

	~Cube();


	bool isPrimitiveCollidingWith(Primitive* prim);
	bool isPrimitiveCollidingWith(Cube* prim);
	bool isPrimitiveCollidingWith(Wall* prim);

};
#endif

