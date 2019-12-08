
#ifndef BOUNDS_H
#define BOUNDS_H

#include "Quaternion.h"

class Bounds
{
public:
	float xmin_;
	float xmax_;
	float ymin_;
	float ymax_;
	float zmin_;
	float zmax_;
	float height_;
	float width_;
	float depth_;
	Bounds(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
	~Bounds();

	Vector3D* rotatedPoints(Quaternion q);
};

#endif