#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector3D.h"
#include "Quaternion.h"

class RigidBody
{
protected:

	float inverseMass_;
	float linearDamping_;
	float angularDamping_;

	Vector3D position_;
	Vector3D velocity_;

	Quaternion orientation_;
	Vector3D rotation_; //velocité angulaire

	Matrix3 transformMatrix_;
	Matrix3 inverseInertiaTensor_;

	//Forces
	Vector3D forceAccum_;
	Vector3D torqueAccum_;

public:

	RigidBody(float mass, Vector3D position, float linearDamping, float angularDamping) :
		inverseMass_(1 / mass), position_(position), linearDamping_(linearDamping), angularDamping_(angularDamping_) {
		orientation_ = Quaternion(0., 0., 0., 1.);
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

	//Forces
	void addForce(Vector3D force);

	//Torques
	void addTorque(Vector3D torque);

	//Applique F a un point précis de l'objet. (Repère Monde)
	void addForceAtPoint(Vector3D force, Vector3D point);

	//Applique F a un point précis de l'objet. (Repère Local)
	void addForceAtBodyPoint(Vector3D force, Vector3D point);

	//Compute the new orientation, velocities and position for the next frame.
	void integrate(float elapsedTime);
	
	//Vide les accumulateurs
	void clearAccumulators();

	////Methodes virtuelles
	//Calcul transformMatrix et moment d'inertie
	void calculDonneesDerivees() {};
	//Display du rigid body
	void display() {};
};

#endif

