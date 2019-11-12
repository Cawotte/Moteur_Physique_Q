#include "Vector3D.h"
#include "Quaternion.h"
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

class RigidBody
{
private:
	float inverseMass_;
	float linearDamping_;
	float angularDamping_;

	Vector3D position_;
	Vector3D velocity_;

	Quaternion orientation_;
	Vector3D rotation_; //velocit� angulaire

	Matrix3 transformMatrix_;
	Matrix3 inverseInertiaTensor_;

	//Forces
	Vector3D forceAccum_;
	Vector3D torqueAccum_;


	void clearAccumulators();

public:

	RigidBody(float mass, Vector3D position, float linearDamping, float angularDamping) :
		inverseMass_(1 / mass), position_(position), linearDamping_(linearDamping), angularDamping_(angularDamping_) {

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

	//Applique F a un point pr�cis de l'objet. (Rep�re Monde)
	void addForceAtPoint(Vector3D force, Vector3D point);

	//Applique F a un point pr�cis de l'objet. (Rep�re Local)
	void addForceAtBodyPoint(Vector3D force, Vector3D point);

	//Compute the new orientation, velocities and position for the next frame.
	void integrate(float elapsedTime);
};

#endif

