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
		bounds_.xmax_ = originalBounds_.xmax_ + body_->getPosition().x;
		bounds_.xmin_ = originalBounds_.xmin_ + body_->getPosition().x;
		bounds_.ymax_ = originalBounds_.ymax_ + body_->getPosition().y;
		bounds_.ymin_ = originalBounds_.ymin_ + body_->getPosition().y;
		bounds_.zmax_ = originalBounds_.zmax_ + body_->getPosition().z;
		bounds_.zmin_ = originalBounds_.zmin_ + body_->getPosition().z;
	}
}