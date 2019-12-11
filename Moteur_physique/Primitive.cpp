#include "Primitive.h"

// Rôle : Constructeur - Initialise le RigidBody et les Bounds
// Entrées : Le RigidBody et les bounds_
// Sortie : Aucune
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

// Rôle : Destructeur - Détruit l'objet
// Entrées : Aucune
// Sortie : Aucune
Primitive::~Primitive()
{
}

// Rôle : Pivote un point selon une orientation 
// Entrées : Le point à pivoter et l'orientation en question
// Sortie : Le point pivoté
Vector3D Primitive::pointRotationByQuaternion(Vector3D point, Quaternion q)
{
	Quaternion r{ 0, point.x, point.y, point.z };

	Quaternion q_conj{q.r_, -q.i_, -q.j_, -q.k_};

	Quaternion result = (q * r) * q_conj;

	return Vector3D(result.i_, result.j_, result.k_);
}

// Rôle : Mise à jour des bounds_
// Entrées : Aucune
// Sortie : Aucune
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
		Vector3D* points = new Vector3D[2];
		points[0] = Vector3D{ bounds_.xmin_, bounds_.ymin_, bounds_.zmin_ };
		points[1] = Vector3D{ bounds_.xmax_, bounds_.ymax_, bounds_.zmax_ };
		Quaternion q = body_->getOrientation();
		//points[0] = pointRotationByQuaternion(points[0], q);
		//points[1] = pointRotationByQuaternion(points[1], q);
		bounds_.xmax_ = points[1].x;
		bounds_.xmin_ = points[0].x;
		bounds_.ymax_ = points[1].y;
		bounds_.ymin_ = points[0].y;
		bounds_.zmax_ = points[1].z;
		bounds_.zmin_ = points[0].z;
	}
}