#include "Wall.h"

Wall::Wall(typeWall type) {

	Bounds b;
	type_ = type;

	switch (type) {

	case upWall:
		b.xmin_ = 0.f;
		b.xmax_ = 39.f;
		b.ymin_ = 0.f;
		b.ymax_ = 39.f;
		b.zmin_ = 39.f;
		b.zmax_ = 40.f;
		normal_.x = 0.f;
		normal_.y = 0.f;
		normal_.z = -1.f;
		break;

	case downWall:
		b.xmin_ = 0.f;
		b.xmax_ = 39.f;
		b.ymin_ = 0.f;
		b.ymax_ = 39.f;
		b.zmin_ = -1.f;
		b.zmax_ = 0.f;
		normal_.x = 0.f;
		normal_.y = 0.f;
		normal_.z = 1.f;
		break;

	case rightWall:
		b.xmin_ = 0.f;
		b.xmax_ = 39.f;
		b.ymin_ = 39.f;
		b.ymax_ = 40.f;
		b.zmin_ = 0.f;
		b.zmax_ = 39.f;
		normal_.x = 0.f;
		normal_.y = -1.f;
		normal_.z = 0.f;
		break;

	case leftWall:
		b.xmin_ = 0.f;
		b.xmax_ = 39.f;
		b.ymin_ = -1.f;
		b.ymax_ = 0.f;
		b.zmin_ = 0.f;
		b.zmax_ = 39.f;
		normal_.x = 0.f;
		normal_.y = 1.f;
		normal_.z = 0.f;
		break;

	case frontWall:
		b.xmin_ = 39.f;
		b.xmax_ = 40.f;
		b.ymin_ = 0.f;
		b.ymax_ = 39.f;
		b.zmin_ = 0.f;
		b.zmax_ = 39.f;
		normal_.x = -1.f;
		normal_.y = 0.f;
		normal_.z = 0.f;
		break;

	case behindWall:
		b.xmin_ = -1.f;
		b.xmax_ = 0.f;
		b.ymin_ = 0.f;
		b.ymax_ = 39.f;
		b.zmin_ = 0.f;
		b.zmax_ = 39.f;
		normal_.x = 1.f;
		normal_.y = 0.f;
		normal_.z = 0.f;
		break;

	}
	setBounds(b);
}


Wall::~Wall()
{
}
