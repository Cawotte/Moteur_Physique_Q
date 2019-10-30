#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle* pa1, Particle* pa2, float restit, float dPene, Vector3D n): restit_(restit), dPene_(dPene), n_(n.normalized())
{
	particles_[0] = pa1;
	particles_[1] = pa2;
	vs_ = calculVs();
}

ParticleContact::~ParticleContact()
{
}

void ParticleContact::resolve(float t) {
	resolveInterpenetration();
	resolveVelocity();
}

float ParticleContact::calculVs() {

	Vector3D closingVelocityA = particles_[0]->getVit();
	//Cas d'un sol
	if (particles_[1] == NULL) {

		return closingVelocityA.dotProd(n_);
		
		/*
		Vector3D closingVelocityA = particles_[0]->getVit();
		float j = (closingVelocityA).dotProd(n_) * restit_;
		return j; */
	}
	//Cas de 2 particules
	else {

		Vector3D closingVelocityB = particles_[1]->getVit();
		return (closingVelocityA - closingVelocityB).dotProd(n_);

		
		/*
		float factor = (-1 + restit_) / (particles_[0]->getMassInv() + particles_[1]->getMassInv());
		float j = (closingVelocityA - closingVelocityB).dotProd(n_) * factor; 
		return j; */
	}
}

void ParticleContact::resolveVelocity() {

	if (vs_ <= 0) return; //ils ne se rapprochent pas et non donc pas besoin d'etre �loign�s

	float vsP = -restit_ * vs_;

	//Cas d'un sol
	if (particles_[1] == NULL) {

		particles_[0]->setVit(particles_[0]->getVit() + n_ * vsP);

		//particles_[0]->setVit(particles_[0]->getVit() + n_* vs_ * particles_[0]->getMassInv());
	}
	//Cas de 2 particules
	else {


		particles_[0]->setVit(particles_[0]->getVit() + n_ * vsP * particles_[0]->getMassInv());
		particles_[1]->setVit(particles_[1]->getVit() - n_ * vsP * particles_[1]->getMassInv());

		//particles_[0]->setVit(particles_[0]->getVit() + n_ * vs_ * particles_[0]->getMassInv());
		//particles_[1]->setVit(particles_[1]->getVit() - n_ * vs_ * particles_[1]->getMassInv());

	}
}

void ParticleContact::resolveInterpenetration() {
	//Cas d'un sol
	if (particles_[1] == NULL) {
		particles_[0]->setPos(*particles_[0]->getPos() + n_ * -dPene_);
	}
	//Cas de 2 particules
	else {
		float ma = 1 / particles_[0]->getMassInv();
		float mb = 1 / particles_[1]->getMassInv();

		Vector3D deltaPA = n_ * (mb / (ma + mb)) * dPene_;
		Vector3D deltaPB = n_ * (ma / (ma + mb)) * dPene_ * - 1;

		particles_[0]->setPos(*particles_[0]->getPos() + deltaPA);
		particles_[1]->setPos(*particles_[1]->getPos() + deltaPB);
	}
}
