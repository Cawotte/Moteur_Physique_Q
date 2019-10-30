#include "ParticleForceRegister.h"

ParticleForceRegister::ParticleForceRegister()
{
}


ParticleForceRegister::~ParticleForceRegister()
{
	clear();
}

void ParticleForceRegister::add(Particle* p, ParticleForceGenerator* fg) {
	ForceRecord fr;
	fr.fg = fg;
	fr.p = p;
	register_.push_back(fr);
}


void ParticleForceRegister::add(std::vector<ForceRecord> otherRegister) {
		
	std::vector<ForceRecord>::iterator it;
	for (it = otherRegister.begin(); it != otherRegister.end(); it++)
	{
		this->add(it->p, it->fg);
	}
}

void ParticleForceRegister::remove() {
	register_.pop_back();
}

void ParticleForceRegister::clear() {
	std::vector<ForceRecord>::iterator it;
	register_.clear();
}

void ParticleForceRegister::updateForces(float t) {
	std::vector<ForceRecord>::iterator it;
	for (it = register_.begin(); it != register_.end(); it++)
	{
		if (it->p != NULL) {
			it->fg->updateForce(it->p, t);
		}
	}
}