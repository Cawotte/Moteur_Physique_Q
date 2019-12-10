
#include "GravityFG.h"

// R�le : Calcule la gravit� en fonction du RigidBody et du temps de frame pass�s en param�tres
// Entr�es : RigidBody pour lequel calculer la force de gravit� et la dur�e de la frame
// Sortie : Aucune
void GravityFG::updateForce(RigidBody* rb, float t) {
	//Si la masse est positive
	if (rb->getInverseMass() > 0) {
		//calcule la force gravitationnelle et l'ajoute au RigidBody
		rb->addForce(gravity_ * (1 / rb->getInverseMass()));
	}
}