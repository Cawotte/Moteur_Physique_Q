#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector3D.h"
#include "Quaternion.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : RigidBody
// But : Représentation physique d'un objet
//		 Permet de gérer les opérations concernant la physique
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RigidBody
{
protected:
	//Inverse de la masse
	float inverseMass_;
	//Damping linéraire et angulaires
	float linearDamping_;
	float angularDamping_;
	//Position
	Vector3D position_;
	//Vélocité linéaire
	Vector3D velocity_;
	//Orientation
	Quaternion orientation_;
	//Velocité angulaire
	Vector3D rotation_; 
	//Matrice de tranformation
	Matrix3 transformMatrix_;
	//Inverse du moment d'intertie
	Matrix3 inverseInertiaTensor_;

	//Forces
	Vector3D forceAccum_;
	Vector3D torqueAccum_;

public:
	//Constructeur avec initialisation des attributs
	RigidBody(float mass, Vector3D position, Quaternion orientation, float linearDamping, float angularDamping) :
		inverseMass_(1 / mass), position_(position), orientation_(orientation), linearDamping_(linearDamping), angularDamping_(angularDamping) {
	}

	#pragma region Getter

	float getInverseMass() {
		return inverseMass_;
	}

	float getLinearDamping() {
		return linearDamping_;
	}

	Vector3D getPosition() {
		return position_;
	}

	Vector3D getVelocity() {
		return velocity_;
	}

	Quaternion getOrientation() {
		return orientation_;
	}

	Vector3D getRotation() {
		return rotation_;
	}

	Matrix3 getTransformMatrix() {
		return transformMatrix_;
	}
	#pragma endregion

	#pragma region Setter
	void setPosition(Vector3D position) {
		position_ = position;
	}

	void setVelocity(Vector3D velocity) {
		velocity_ = velocity;
	}

	void setOrientation(Quaternion orientation) {
		orientation_ = orientation;
	}

	void setRotation(Vector3D rotation) {
		rotation_ = rotation;
	}

	#pragma endregion

	//Ajoute une force
	void addForce(Vector3D force);

	//Ajoute un torque
	void addTorque(Vector3D torque);

	//Applique une force a un point précis de l'objet. (Repère Monde)
	void addForceAtPoint(Vector3D force, Vector3D point);

	//Applique une force a un point précis de l'objet. (Repère Local)
	void addForceAtBodyPoint(Vector3D force, Vector3D point);

	//Calcule les nouvelles orientations, vélocités et position pour la prochaine frame
	void integrate(float elapsedTime);
	
	//Vide les accumulateurs
	void clearAccumulators();

	////Methodes virtuelles
	//Calcul transformMatrix et moment d'inertie
	void calculDonneesDerivees() {};
	//Affichage du RigidBody
	void display() {};
};

#endif

