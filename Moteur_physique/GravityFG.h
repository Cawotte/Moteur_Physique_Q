#ifndef GRAVITY_FORCE_GENERATOR
#define GRAVITY_FORCE_GENERATOR

#include "ForceGenerator.h"

class GravityFG : public ForceGenerator
{
private:

	Vector3D gravity_;

public:
	GravityFG(Vector3D g) : gravity_(g) {
	}

	void updateForce(RigidBody* rb, float t);

	Vector3D getGravity() { return gravity_; }
	void setGravity(Vector3D gravity) { gravity_ = gravity; }
};

#endif