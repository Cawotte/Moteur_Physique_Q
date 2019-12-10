#ifndef WALL_H
#define WALL_H

#include "Primitive.h"
#include "Cube.h"

enum typeWall {
	frontWall,
	rightWall,
	leftWall,
	upWall,
	downWall,
	behindWall
};

class Wall : public Primitive {

private:

	typeWall type_;


	Vector3D normal_;
	float offset_ = 0.f;

public:

	Wall(typeWall type);
	~Wall();

	bool isPrimitiveCollidingWith(Primitive* prim);
	bool isPrimitiveCollidingWith(Cube* prim);
	bool isPrimitiveCollidingWith(Wall* prim);

	typeWall getType() { return type_; }
	Vector3D getNormal() { return normal_; }
};

#endif