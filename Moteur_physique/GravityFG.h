#ifndef GRAVITY_FORCE_GENERATOR
#define GRAVITY_FORCE_GENERATOR

#include "ForceGenerator.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : GravityFC - h�rite de ForceGenerator
// But : Represente une boite
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GravityFG : public ForceGenerator
{
private:
	//Vecteur gravit�
	Vector3D gravity_;

public:
	//Constructeur
	GravityFG(Vector3D g) : gravity_(g) {	}
	//Calcule la gravit� en fonction du RigidBody et du temps de frame pass�s en param�tres
	void updateForce(RigidBody* rb, float t);
	//Getter de la gravit�
	Vector3D getGravity() { return gravity_; }
	//Setter de la gravit�
	void setGravity(Vector3D gravity) { gravity_ = gravity; }
};

#endif