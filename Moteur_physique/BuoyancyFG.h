#ifndef BUOYANCY_FORCE_GENERATOR
#define BUOYANCY_FORCE_GENERATOR

#include "ParticleForceGenerator.h"

class BuoyancyFG: public ParticleForceGenerator
{
private:

	float s_ = 2.f;
	// if r = 2.f
	float v_ = 33.51f;
	float zWater_ = 0.f;
	float density_ = 1000.f;

public:

	BuoyancyFG();
	~BuoyancyFG();

	void updateForce(Particle* p, float t);
};

#endif