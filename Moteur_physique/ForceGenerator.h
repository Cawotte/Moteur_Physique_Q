#ifndef PARTICLE_FORCE_GENERATOR
#define PARTICLE_FORCE_GENERATOR

#include "RigidBody.h"

//Interface des g�n�rateurs de force pour les particules
class ForceGenerator {

public:
	virtual void updateForce(RigidBody* rb, float t) = 0;
};

#endif