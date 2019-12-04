#pragma once
class Bounds
{
public:
	double xmin_;
	double xmax_;
	double ymin_;
	double ymax_;
	double zmin_;
	double zmax_;
	double height_;
	double width_;
	double depth_;
	Bounds(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
	Bounds();
	~Bounds();
};

