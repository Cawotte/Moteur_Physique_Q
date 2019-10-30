#ifndef PARTICLE_FORCE_GENERATOR
#define PARTICLE_FORCE_GENERATOR

#include "Particle.h"

//Interface des g�n�rateurs de force pour les particules
class ParticleForceGenerator {

public:
	virtual void updateForce(Particle* p, float t) = 0;
};

#endif