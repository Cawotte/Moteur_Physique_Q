#include "RigidBody.h"

void RigidBody::addForce(Vector3D force)
{
	forceAccum_ = forceAccum_ + force;
}

void RigidBody::addTorque(Vector3D torque) {
	torqueAccum_ = torqueAccum_ + torque;
}

void RigidBody::clearAccumulators()
{
	forceAccum_ = Vector3D(0, 0, 0);
	torqueAccum_ = Vector3D(0, 0, 0);
}

void RigidBody::addForceAtPoint(Vector3D force, Vector3D point)
{
	point = point - position_;

	addForce(force);

	addTorque(point.crossProd(force));

}

void RigidBody::addForceAtBodyPoint(Vector3D force, Vector3D point)
{
	point = point.fromLocalToWorld(transformMatrix_);

	addForceAtPoint(force, point);
}

void RigidBody::integrate(float elapsedTime)
{
	
	// 1 - Calculer acc�l�ration lin�aire
	Vector3D linearAcc = forceAccum_ * inverseMass_; //p**

	// 2 - Calculer acc�l�ration angulaire
	Vector3D angularAcc = torqueAccum_.multiply(inverseInertiaTensor_); //O**

	// 3 - Mettre � jour v�locit� lin�aire
	velocity_ = velocity_ + linearAcc * elapsedTime;

	// 4 - Mettre � jour v�locit� angulaire
	rotation_ = rotation_ * std::powf(angularDamping_, elapsedTime) + angularAcc * elapsedTime;

	// 5 - Ajouter le drag aux deux v�locit�s (� am�liorer avec k1 * vit + k2 * vit ** 2)
	velocity_ = velocity_ * 0.9f;
	rotation_ = rotation_ * 0.9f;

	// 6 - Mettre � jour la position
	position_ = position_ + velocity_ * elapsedTime;

	// 7 - Mettre � jour l'orientation
	orientation_.updateAngularVelocity(rotation_, elapsedTime);

	// 8 - Calculer TransformMatrix et InertiaMatrix
	calculDonneesDerivees();

	// 9 - Clear Accumulators
	clearAccumulators();

}
