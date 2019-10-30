#include "WeakSpringFG.h"

WeakSpringFG::WeakSpringFG(float k, float d) : k_(k), d_(d)
{
}


WeakSpringFG::~WeakSpringFG()
{
}


void WeakSpringFG::updateForce(Particle* p, float t) {
	float gamma = 0.5f * sqrt(4 * k_ - d_ * d_);
	Vector3D c = *(p->getPos()) * (d_ / (2 * gamma)) + p->getVit() * (1 / gamma);
	Vector3D pt = *(p->getPos()) * cos(gamma * t) + c * sin(gamma * t);
	p->addForce((pt - *(p->getPos())) * (1 / (t * t)) - p->getVit());
}
