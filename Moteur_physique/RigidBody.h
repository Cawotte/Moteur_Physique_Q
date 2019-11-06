#include "Vector3D.h"
#include "Quaternion.h"
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

class RigidBody
{
private:
	float inverseMass_;
	float linearDamping_;

	Vector3D position_;
	Vector3D velocity_;

	Quaternion orientation_;
	Vector3D rotation_;

	Matrix3 transformMatrix_;


public:

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
};

#endif

