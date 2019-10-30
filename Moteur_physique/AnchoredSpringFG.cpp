#include "AnchoredSpringFG.h"

void AnchoredSpringFG::updateForce(Particle* p, float t) {

	Vector3D d = *p->getPos() - anchor_;

	p->addForce(
		d.normalized() * -k_ * (d.norm() - l0_));

}