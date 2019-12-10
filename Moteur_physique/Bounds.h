
#ifndef BOUNDS_H
#define BOUNDS_H

#include "Quaternion.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Bounds
// But : Représente les 8 extrémités d'un parallélépipède rectangle, ainsi que sa largeur/hauteur/profondeur
//		 Utilisée afin de d�tecter les contacts entre des primitives
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Bounds
{
public:
	//extrémités minimum et maximum en largeur, hauteur et profondeur de l'objet associé. Valeurs par défaut : 0
	float xmin_ = 0.f;
	float xmax_ = 0.f;
	float ymin_ = 0.f;
	float ymax_ = 0.f;
	float zmin_ = 0.f;
	float zmax_ = 0.f;
	//hauteur, largeur et profondeur associées
	float height_ = 0.f;
	float width_ = 0.f;
	float depth_ = 0.f;
	//Constructeur avec les extrémités en paramètres
	Bounds(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
	//Constructeur par défaut
	Bounds() {};
	//Destructeur
	~Bounds();
	//Calcule le point central de l'objet associé
	Vector3D getCenter();

};

#endif