#ifndef GRAVITY_FORCE_GENERATOR
#define GRAVITY_FORCE_GENERATOR

#include "ForceGenerator.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : GravityFC - hérite de ForceGenerator
// But : Represente une boite
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GravityFG : public ForceGenerator
{
private:
	//Vecteur gravité
	Vector3D gravity_;

public:
	//Constructeur
	GravityFG(Vector3D g) : gravity_(g) {	}
	//Calcule la gravité en fonction du RigidBody et du temps de frame passés en paramètres
	void updateForce(RigidBody* rb, float t);
	//Getter de la gravité
	Vector3D getGravity() { return gravity_; }
	//Setter de la gravité
	void setGravity(Vector3D gravity) { gravity_ = gravity; }
};

#endif