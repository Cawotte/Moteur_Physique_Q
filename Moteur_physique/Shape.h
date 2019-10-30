#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GlutUtils.h"

#include "Vector3D.h"
#include "Contact.h"

class Shape;
class Rect3D;
class Sphere;

// Classe abstraite gérant l'affichage des particules, deux dérivées pour l'instant : sphère et rectangle 3D
class Shape
{

protected:


	std::shared_ptr<Vector3D> position_;
	Vector3D color_;

public:

	//Constructors
	Shape(std::shared_ptr<Vector3D> pos, Vector3D rgb) : position_(pos), color_(rgb) { }

	Vector3D getColor() {
		return color_;
	}

	Vector3D getPos() {
		return *position_;
	}

	void setColor(float r, float g, float b) {
		color_ = Vector3D(r, g, b);
	}

	void setColor(Vector3D rgb) {
		color_ = rgb;
	}

	virtual void draw() = 0; //pure virtual function

	//Collisions with DOUBLE DISPATCHIING
	virtual Contact collideWith(Shape& shape) = 0;
	virtual Contact collideWithInternal(Sphere& sphere) = 0;
	virtual Contact collideWithInternal(Rect3D& rect) = 0;


};

class Rect3D : public Shape {

private:

	float width_;
	float height_;
	float depth_;

public:

	//Constructors
	Rect3D(std::shared_ptr<Vector3D> pos, Vector3D color, float w = 2, float h = 2, float p = 2) : width_(w), height_(h), depth_(p), Shape(pos, color) { }

	Vector3D getMinPos() {
		return Vector3D(position_->x - width_ / 2, position_->y - height_ / 2, position_->z - depth_ / 2);
	}

	Vector3D getMaxPos() {
		return Vector3D(position_->x + width_ / 2, position_->y + height_ / 2, position_->z + depth_ / 2);
	}

	void draw();


	//Collisions with DOUBLE DISPATCHIING
	Contact collideWith(Shape& shape);
	Contact collideWithInternal(Sphere& sphere);
	Contact collideWithInternal(Rect3D& rect);
};

class Sphere : public Shape {

private:

	float radius_;

public:

	//Constructors
	Sphere(std::shared_ptr<Vector3D> pos, Vector3D color,  float radius_ = 2) : radius_(radius_), Shape(pos, color) { }

	float getRadius();

	void draw();

	//Collisions with DOUBLE DISPATCHIING
	Contact collideWith(Shape& shape);
	Contact collideWithInternal(Sphere& sphere);
	Contact collideWithInternal(Rect3D& rect);
};


#endif