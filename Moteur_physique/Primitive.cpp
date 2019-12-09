#include "Primitive.h"

Primitive::Primitive(RigidBody* body, Bounds b)
{

	bounds_ = b;
	body_ = body;
}


Primitive::~Primitive()
{
}

Vector3D Primitive::pointRotationByQuaternion(Vector3D point, Quaternion q)
{
	Quaternion r{ 0, point.x, point.y, point.z };

	Quaternion q_conj{q.r_, -q.i_, -q.j_, -q.k_};

	Quaternion result = (q * r) * q_conj;

	return Vector3D(result.i_, result.j_, result.k_);
}

bool Primitive::pointIsWithinBox(Vector3D point, Vector3D* p)
{
	float xLenght = (p[1] - p[0]).norm();
	float yLenght = (p[3] - p[0]).norm();
	float zLenght = (p[4] - p[0]).norm();

	Vector3D xLocal = (p[1] - p[0]) * (1.f / xLenght);
	Vector3D yLocal = (p[3] - p[0]) * (1.f / yLenght);
	Vector3D zLocal = (p[4] - p[0]) * (1.f / zLenght);

	Vector3D pivot = p[8];

	Vector3D v = point - pivot;

	float px = abs(v.dotProd(xLocal));
	float py = abs(v.dotProd(yLocal));
	float pz = abs(v.dotProd(zLocal));

	return (2 * px <= xLenght &&
			2 * py <= yLenght &&
			2 * pz <= zLenght
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

	points[8] = (points[0] + points[7]) * 0.5f;


	Quaternion q = body_->getOrientation();

	//Points d�place autour du centre du pivot
	//Et rotationn�s
	for (int i = 0; i < 8; i++) {
		points[i] = points[i] + body_->getPosition();
		points[i] = pointRotationByQuaternion(points[i], q);
	}

	return points;
}