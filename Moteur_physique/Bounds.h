
#ifndef BOUNDS_H
#define BOUNDS_H

#include "Quaternion.h"

class Bounds
{
public:
	float xmin_ = 0.f;
	float xmax_ = 0.f;
	float ymin_ = 0.f;
	float ymax_ = 0.f;
	float zmin_ = 0.f;
	float zmax_ = 0.f;
	float height_ = 0.f;
	float width_ = 0.f;
	float depth_ = 0.f;

	Bounds(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);

	Bounds() {};
	~Bounds();

	Vector3D getCenter();

};

#endif