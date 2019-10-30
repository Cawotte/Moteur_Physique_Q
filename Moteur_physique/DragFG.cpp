#include "DragFG.h"
#include <cmath>

void DragFG::updateForce(Particle* p, float t) {

	Vector3D vitUnit = p->getVit().normalized();
	float dragForce = k1_ * p->getVit().norm() +
						k2_ * pow(p->getVit().norm(), 2);

	p->addForce(vitUnit * dragForce * -1.);

}
