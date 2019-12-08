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
	Vector3D u = (p[0] - p[2]).crossProd(p[0] - p[3]);
	Vector3D v = (p[0] - p[1]).crossProd(p[0] - p[3]);
	Vector3D w = (p[0] - p[1]).crossProd(p[0] - p[2]);

	return (u.x > u.dotProd(p[0]) && u.x < u.dotProd(p[1]) &&
		v.x > u.dotProd(p[0]) && v.x < v.dotProd(p[2]) &&
		w.x > u.dotProd(p[0]) && w.x < w.dotProd(p[3])
		);

}

Vector3D* Primitive::rotatedRepere()
{
	Vector3D* points = new Vector3D[8];

	//Points du repres
	points[0] = Vector3D{ bounds_.xmin_, bounds_.ymin_, bounds_.zmin_ };
	points[1] = Vector3D{ bounds_.xmax_, bounds_.ymin_, bounds_.zmin_ };
	points[2] = Vector3D{ bounds_.xmin_, bounds_.ymax_, bounds_.zmin_ };
	points[3] = Vector3D{ bounds_.xmin_, bounds_.ymin_, bounds_.zmax_ };

	points[4] = Vector3D{ bounds_.xmax_, bounds_.ymax_, bounds_.zmax_ };
	points[5] = Vector3D{ bounds_.xmin_, bounds_.ymax_, bounds_.zmax_ };
	points[6] = Vector3D{ bounds_.xmax_, bounds_.ymin_, bounds_.zmax_ };
	points[7] = Vector3D{ bounds_.xmax_, bounds_.ymax_, bounds_.zmin_ };

	Quaternion q = body_->getOrientation();

	//Points déplace autour du centre du pivot
	//Et rotationnés
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
