#ifndef PARTICLE_CONTACT
#define PARTICLE_CONTACT

#include "Particle.h"

class ParticleContact
{
private:
	Particle* particles_[2];
	float restit_;
	float dPene_;
	float vs_;

	Vector3D n_; //Dans le sens particles_[0] -> particles_[1]

public:

	ParticleContact(Particle* pa1, Particle* pa2, float restit, float dPene, Vector3D n);
	~ParticleContact();

	float getVs() {
		return vs_;
	}

	void resolve(float t);
	float calculVs();
	void resolveVelocity();
	void resolveInterpenetration();



};

#endif