#ifndef GRAVITY_FORCE_GENERATOR
#define GRAVITY_FORCE_GENERATOR

#include "ParticleForceGenerator.h"

class GravityFG : public ParticleForceGenerator
{
private:

	Vector3D gravity_;

public:
	GravityFG(Vector3D g) : gravity_(g) {
	}

	void updateForce(Particle* p, float t);

	Vector3D getGravity() { return gravity_; }
	void setGravity(Vector3D gravity) { gravity_ = gravity; }
};

#endif