#ifndef ANCHORED_SPRING_FORCE_GENERATOR
#define ANCHORED_SPRING_FORCE_GENERATOR

#include "ParticleForceGenerator.h"
class AnchoredSpringFG :
	public ParticleForceGenerator
{
private:
	Vector3D anchor_;
	float k_; //elasticity
	float l0_; //distance between particles at rest

public:

	//constructors
	AnchoredSpringFG(Vector3D anchor, float k, float l0) :
		anchor_(anchor), k_(k), l0_(l0) {};

	void updateForce(Particle* p, float t);

};


#endif

