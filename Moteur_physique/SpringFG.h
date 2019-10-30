#ifndef SPRING_FORCE_GENERATOR
#define SPRING_FORCE_GENERATOR

#include "ParticleForceGenerator.h"
class SpringFG :
	public ParticleForceGenerator
{

private:
	Particle* other_;
	float k_; //elasticity
	float l0_; //distance between particles at rest

public:

	//constructors
	SpringFG(Particle* other, float k, float l0) :
		other_(other), k_(k), l0_(l0) {};

	void updateForce(Particle* p, float t);

};

#endif

