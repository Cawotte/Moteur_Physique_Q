#ifndef PARTICLEFORCEREGISTER_H
#define PARTICLEFORCEREGISTER_H

#include <vector>
#include "Particle.h"
#include "ParticleForceGenerator.h"

struct ForceRecord {
	Particle* p;
	ParticleForceGenerator* fg;
};

class ParticleForceRegister {

private:

	std::vector<ForceRecord> register_;

public:

	void add(Particle* p, ParticleForceGenerator* fg);
	void add(std::vector<ForceRecord> otherRegister);
	void remove();
	void clear();
	void updateForces(float t);

	std::vector<ForceRecord> getRegister() {
		return register_;
	}

	ParticleForceRegister();
	~ParticleForceRegister();
};

#endif