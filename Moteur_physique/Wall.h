#ifndef WALL_H
#define WALL_H

#include "Primitive.h"

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

	typeWall getType() { return type_; }
};

#endif