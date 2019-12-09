#include "Primitive.h"



Vector3D Primitive::pointRotationByQuaternion(Vector3D point, Quaternion q)
{
	Quaternion r{ 0, point.x, point.y, point.z };

	Quaternion q_conj{q.r_, -q.i_, -q.j_, -q.k_};

	Quaternion result = (q * r) * q_conj;

	return Vector3D(result.i_, result.j_, result.k_);
}

bool Primitive::pointIsWithinBox(Vector3D point, Vector3D* p)
{
	Vector3D u = p[0] - p[1];
	Vector3D v = p[0] - p[3];
	Vector3D w = p[0] - p[4];

	return (u.x > u.dotProd(p[0]) && u.x < u.dotProd(p[1]) &&
		v.x > v.dotProd(p[0]) && v.x < v.dotProd(p[3]) &&
		w.x > w.dotProd(p[0]) && w.x < w.dotProd(p[4])
		);
	
}

Vector3D* Primitive::rotatedRepere()
{
	Vector3D* points = new Vector3D[9];

	//Points du repres
	points[0] = Vector3D{ bounds_.xmin_, bounds_.ymin_, bounds_.zmin_ }; //p1
	points[1] = Vector3D{ bounds_.xmax_, bounds_.ymin_, bounds_.zmin_ }; //p2
	points[3] = Vector3D{ bounds_.xmin_, bounds_.ymax_, bounds_.zmin_ }; //p4
	points[4] = Vector3D{ bounds_.xmin_, bounds_.ymin_, bounds_.zmax_ }; //p5
	
	points[2] = Vector3D{ bounds_.xmax_, bounds_.ymax_, bounds_.zmin_ }; //p3
	points[6] = Vector3D{ bounds_.xmax_, bounds_.ymax_, bounds_.zmax_ }; //p7
	points[7] = Vector3D{ bounds_.xmin_, bounds_.ymax_, bounds_.zmax_ }; //p8
	points[5] = Vector3D{ bounds_.xmax_, bounds_.ymin_, bounds_.zmax_ }; //p6

	points[8] = Vector3D{ (bounds_.xmin_ + bounds_.xmax_) /2.f ,
						(bounds_.ymin_ + bounds_.ymax_) / 2.f , 
						 (bounds_.zmin_ + bounds_.zmax_) / 2.f , }; 


	Quaternion q = body_->getOrientation();

	//Points d�place autour du centre du pivot
	//Et rotationn�s
	for (int i = 0; i < 8; i++) {
		points[i] = points[i] + body_->getPosition();
		points[i] = pointRotationByQuaternion(points[i], q);
	}

	return points;
}

Primitive::Primitive(RigidBody* body, Bounds b)
{

	bounds_ = b;
	body_ = body;
}


Primitive::~Primitive()
{
}

bool Primitive::hasCollision(Primitive* primitive)
{

	Vector3D* a = rotatedRepere();
	Vector3D* b = primitive->rotatedRepere();

	for (int i = 0; i < 8; i++) {

		if (pointIsWithinBox(b[i], a)) {
			return true;
		}
	}

	return false;
}
