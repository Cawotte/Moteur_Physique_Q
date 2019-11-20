#ifndef BOX_H
#define BOX_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Box.h
// But : Represente une boite
// Date de creation : 13/11/2019
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RigidBody.h"
#include "Vector3D.h"
#include "GlutUtils.h"
#include "Color.h"

class Box : public RigidBody
{
private:
	
public:

	float dx_;
	float dy_;
	float dz_;

	Vector3D color_ = Color::blue;

	Box(float mass, Vector3D position, Quaternion orientation, float linearDamping, float angularDamping, float dx, float dy, float dz);

	void calculDonneesDerivees();

	void display();

	void setColor(Vector3D color) { color_ = color; }

	~Box();
};

#endif