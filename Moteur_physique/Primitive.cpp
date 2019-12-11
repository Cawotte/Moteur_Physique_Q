#include "Primitive.h"

Primitive::Primitive(RigidBody* body, Bounds b)
{
	bounds_ = b;
	originalBounds_.xmax_ = b.xmax_ - body->getPosition().x;
	originalBounds_.xmin_ = b.xmin_ - body->getPosition().x;
	originalBounds_.ymax_ = b.ymax_ - body->getPosition().y;
	originalBounds_.ymin_ = b.ymin_ - body->getPosition().y;
	originalBounds_.zmax_ = b.zmax_ - body->getPosition().z;
	originalBounds_.zmin_ = b.zmin_ - body->getPosition().z;
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

void Primitive::updateBounds() {
	if (body_ != NULL) {

		//Déplacement
		bounds_.xmax_ = originalBounds_.xmax_ + body_->getPosition().x;
		bounds_.xmin_ = originalBounds_.xmin_ + body_->getPosition().x;
		bounds_.ymax_ = originalBounds_.ymax_ + body_->getPosition().y;
		bounds_.ymin_ = originalBounds_.ymin_ + body_->getPosition().y;
		bounds_.zmax_ = originalBounds_.zmax_ + body_->getPosition().z;
		bounds_.zmin_ = originalBounds_.zmin_ + body_->getPosition().z;

		//Rotation
		Quaternion q = body_->getOrientation();
		float xmin;
		float xmax;
		float ymin;
		float ymax;
		float zmin;
		float zmax;
		Vector3D* points = new Vector3D[9];
		points[0] = Vector3D{ bounds_.xmin_, bounds_.ymin_, bounds_.zmin_ };
		points[1] = Vector3D{ bounds_.xmin_, bounds_.ymin_, bounds_.zmax_ };
		points[2] = Vector3D{ bounds_.xmin_, bounds_.ymax_, bounds_.zmin_ };
		points[3] = Vector3D{ bounds_.xmin_, bounds_.ymax_, bounds_.zmax_ };
		points[4] = Vector3D{ bounds_.xmax_, bounds_.ymin_, bounds_.zmin_ };
		points[5] = Vector3D{ bounds_.xmax_, bounds_.ymin_, bounds_.zmax_ };
		points[6] = Vector3D{ bounds_.xmax_, bounds_.ymax_, bounds_.zmin_ };
		points[7] = Vector3D{ bounds_.xmax_, bounds_.ymax_, bounds_.zmax_ };
		points[0] = pointRotationByQuaternion(points[0], q);
		xmin = points[0].x;
		xmax = points[0].x;
		ymin = points[0].y;
		ymax = points[0].y;
		zmin = points[0].z;
		zmax = points[0].z;
		for (int i = 1; i < 8; i++) {
			points[i] = pointRotationByQuaternion(points[i], q);
			if (points[i].x < xmin) {
				xmin = points[i].x;
			}
			else if (points[i].x > xmax) {
				xmax = points[i].x;
			}
			if (points[i].y < ymin) {
				ymin = points[i].y;
			}
			else if (points[i].y > ymax) {
				ymax = points[i].y;
			}
			if (points[i].z < zmin) {
				zmin = points[i].z;
			}
			else if (points[i].z > zmax) {
				zmax = points[i].z;
			}
		}
		/*
		bounds_.xmax_ = xmax;
		bounds_.xmin_ = xmin;
		bounds_.ymax_ = ymax;
		bounds_.ymin_ = ymin;
		bounds_.zmax_ = zmax;
		bounds_.zmin_ = zmin;
		*/
	}
}