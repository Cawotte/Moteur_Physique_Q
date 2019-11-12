
#include "GravityFG.h"


void GravityFG::updateForce(RigidBody* rb, float t) {

	//Copié-collé du précédent projet, probablement à changer?

	if (rb->getInverseMass() > 0) {

		rb->addForce(
			gravity_ * (1 / rb->getInverseMass())
		);

	}
}