#include "RigidBody.h"

void RigidBody::addForce(Vector3D force)
{
	forceAccum_ = forceAccum_ + force;
}


void RigidBody::clearAccumulators()
{
	forceAccum_ = Vector3D();
	torqueAccum_ = Vector3D();
}

void RigidBody::addForceAtPoint(Vector3D force, Vector3D point)
{

	//TODO 
}

void RigidBody::addForceAtBodyPoint(Vector3D force, Vector3D point)
{
	//TODO 
}

void RigidBody::integrate(float elapsedTime)
{
	
	// 1 - Calculer accélération linéaire
	Vector3D linearAcc = forceAccum_ * inverseMass_; //p**

	// 2 - Calculer accélération angulaire
	Vector3D angularAcc = inverseInertiaTensor_ * torqueAccum_; //O**

	// 3 - Mettre à jour vélocité linéaire
	velocity_ = velocity_ + linearAcc * elapsedTime;

	// 4 - Mettre à jour vélocité angulaire
	rotation_ = rotation_ * std::powf(angularDamping_, elapsedTime) + angularAcc * elapsedTime;

	// 5 - Ajouter le drag aux deux vélocités

	// 6 - Mettre à jour la position

	// 7 - Mettre à jour l'orientation
	orientation_.updateAngularVelocity(rotation_, elapsedTime);

	// 8 - Calculer TransformMatrix et InertiaMatrix

	// 9 - Clear Accumulators
	clearAccumulators();


}
