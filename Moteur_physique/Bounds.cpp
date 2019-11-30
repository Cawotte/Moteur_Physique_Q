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
	deepth_ = zmax_ - zmin_;
}

Bounds::Bounds()
{
	xmin_ = 0;
	ymin_ = 0;
	zmin_ = 0;
	xmax_ = 0;
	ymax_ = 0;
	zmax_ = 0;
	width_ = xmax_ - xmin_;
	height_ = ymax_ - ymin_;
	deepth_ = zmax_ - zmin_;
}


Bounds::~Bounds()
{
}
