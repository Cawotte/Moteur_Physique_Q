#include "SpringTorque.h"

void SpringTorque::updateForce(RigidBody* rb, float t)
{

	//Calculer p1 et p2 dans le repère monde.
	Vector3D p1world = p1_.fromLocalToWorld(rb->getTransformMatrix());
	Vector3D p2world = p2_.fromLocalToWorld(rb->getTransformMatrix());

	//Calculer vec p1-p2
	Vector3D force = p1world - p2world;

	//Calculer magnitude force
	force = force.normalized()  * springCst_ * (force.norm() - restLenght_);

	//Appliquer la force
	rb->addForceAtPoint(force, p1_);


}
