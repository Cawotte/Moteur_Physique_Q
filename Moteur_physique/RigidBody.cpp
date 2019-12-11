#include "RigidBody.h"

// R�le : Ajoute une force
// Entr�es : La force � ajouter
// Sortie : Aucune
void RigidBody::addForce(Vector3D force)
{
	forceAccum_ = forceAccum_ + force;
}

// R�le : Ajoute un torque
// Entr�es : Le torque � ajouter
// Sortie : Aucune
void RigidBody::addTorque(Vector3D torque) {
	torqueAccum_ = torqueAccum_ + torque;
}

// R�le : Vide les accumulateurs
// Entr�es : Aucune
// Sortie : Aucune
void RigidBody::clearAccumulators()
{
	forceAccum_ = Vector3D(0, 0, 0);
	torqueAccum_ = Vector3D(0, 0, 0);
}

// R�le : Applique une force a un point pr�cis de l'objet. (Rep�re Monde)
// Entr�es : La force � appliquer, le point sur lequel l'appliquer
// Sortie : Aucune
void RigidBody::addForceAtPoint(Vector3D force, Vector3D point)
{
	point = point - position_;

	addForce(force);

	addTorque(point.crossProd(force));

}

// R�le : Applique une force a un point pr�cis de l'objet. (Rep�re Local)
// Entr�es : La force � appliquer, le point sur lequel l'appliquer
// Sortie : Aucune
void RigidBody::addForceAtBodyPoint(Vector3D force, Vector3D point)
{
	point = point.fromLocalToWorld(transformMatrix_);

	addForceAtPoint(force, point);
}

// R�le : Calcule les nouvelles orientations, v�locit�s et position pour la prochaine frame
// Entr�es : La dur�e de la frame
// Sortie : Aucune
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
	//velocity_ = velocity_ * 0.9f;
	//rotation_ = rotation_ * 0.9f;

	// 6 - Mettre � jour la position
	position_ = position_ + velocity_ * elapsedTime;

	// 7 - Mettre � jour l'orientation
	orientation_.updateAngularVelocity(rotation_, elapsedTime);

	// 8 - Calculer TransformMatrix et InertiaMatrix
	calculDonneesDerivees();

	// 9 - Clear Accumulators
	clearAccumulators();

	// Affichage de la nouvelle position pour debug
	//getPosition().display();
}