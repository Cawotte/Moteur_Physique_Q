#ifndef BOX_H
#define BOX_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Box.h
// But : Represente une boite
// Date de creation : 13/11/2019
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RigidBody.h"
#include "Vector3D.h"

class Box : public RigidBody
{
private:

	float dx_;
	float dy_;
	float dz_;

public:
	Box(float mass, Vector3D position, float linearDamping, float angularDamping, float dx, float dy, float dz);

	void calculDonneesDerivees();

	~Box();
};

#endif