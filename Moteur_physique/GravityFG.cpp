
#include "GravityFG.h"

// Rôle : Calcule la gravité en fonction du RigidBody et du temps de frame passés en paramètres
// Entrées : RigidBody pour lequel calculer la force de gravité et la durée de la frame
// Sortie : Aucune
void GravityFG::updateForce(RigidBody* rb, float t) {
	//Si la masse est positive
	if (rb->getInverseMass() > 0) {
		//calcule la force gravitationnelle et l'ajoute au RigidBody
		rb->addForce(gravity_ * (1 / rb->getInverseMass()));
	}
}