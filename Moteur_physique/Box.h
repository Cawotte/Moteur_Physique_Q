#ifndef BOX_H
#define BOX_H

#include "RigidBody.h"
#include "Vector3D.h"
#include "GlutUtils.h"
#include "Color.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Box - h�rite de RigidBody
// But : Represente une boite
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Box : public RigidBody
{
private:
	
public:
	//demi-dimensions : demi-longeur, demi-hauteur, demi-profondeur
	float dx_;
	float dy_;
	float dz_;
	//couleur associ�e de la forme
	Vector3D color_ = Color::blue;
	//Constructeur
	Box(float mass, Vector3D position, Quaternion orientation, float linearDamping, float angularDamping, float dx, float dy, float dz);
	//Calcule la matrice de transformation et l'inverse du moment d'inertie de l'objet associ�
	void calculDonneesDerivees();
	//Dessine la box sur l'�cran
	void display();
	//Met � jour la couleur de la bo�te
	void setColor(Vector3D color) { color_ = color; }
	//Destructeur
	~Box();
};

#endif