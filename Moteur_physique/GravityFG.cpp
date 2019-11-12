
#include "GravityFG.h"


void GravityFG::updateForce(RigidBody* rb, float t) {

	//Copi�-coll� du pr�c�dent projet, probablement � changer?

	if (rb->getInverseMass() > 0) {

		rb->addForce(
			gravity_ * (1 / rb->getInverseMass())
		);

	}
}