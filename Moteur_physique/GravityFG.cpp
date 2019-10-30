
#include "GravityFG.h"


void GravityFG::updateForce(Particle* p, float t) {

	if (p->getMassInv() > 0) {

		p->addForce(
			gravity_ * (1 / p->getMassInv())
		);

	}
}