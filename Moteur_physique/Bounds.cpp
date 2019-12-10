#include "Bounds.h"



Bounds::Bounds(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
	xmin_ = xmin;
	ymin_ = ymin;
	zmin_ = zmin;
	xmax_ = xmax;
	ymax_ = ymax;
	zmax_ = zmax;
	width_ = xmax_ - xmin_;
	height_ = ymax_ - ymin_;
	depth_ = zmax_ - zmin_;
}


Bounds::~Bounds()
{
}

Vector3D Bounds::getCenter()
{
	Vector3D min = Vector3D{xmin_, ymin_, zmin_ }; //p1
	Vector3D max = Vector3D{xmax_, ymax_, zmax_ }; //p1

	return (min + max) * 0.5f;
}

