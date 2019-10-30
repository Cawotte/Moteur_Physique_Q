#include "BuoyancyFG.h"

BuoyancyFG::BuoyancyFG()
{
}


BuoyancyFG::~BuoyancyFG()
{
}

void BuoyancyFG::updateForce(Particle* p, float t) {
	if (p->getPos()->z > (s_ + zWater_))
	{
		return;
	}
	else if (p->getPos()->z <= (zWater_ - s_)) {
		p->addForce(Vector3D(0, 0, v_ * density_));
	}
	else{
		float propWater = (p->getPos()->z - s_ - zWater_) / (2 * s_);
		p->addForce(Vector3D(0, 0, v_ * density_*propWater));
	}
}