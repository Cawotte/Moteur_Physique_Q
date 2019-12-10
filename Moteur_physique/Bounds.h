
#ifndef BOUNDS_H
#define BOUNDS_H

#include "Quaternion.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Bounds
// But : Repr�sente les 8 extr�mit�s d'un parall�l�pip�de rectangle, ainsi que sa largeur/hauteur/profondeur
//		 Utilis� afin de d�tecter les contacts entre des primitives
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Bounds
{
public:
	//extr�mit�s minimum et maximum en largeur, hauteur et profondeur de l'objet associ�. Valeurs par d�faut : 0
	float xmin_ = 0.f;
	float xmax_ = 0.f;
	float ymin_ = 0.f;
	float ymax_ = 0.f;
	float zmin_ = 0.f;
	float zmax_ = 0.f;
	//hauteur, largeur et profondeur associ�es
	float height_ = 0.f;
	float width_ = 0.f;
	float depth_ = 0.f;
	//Constructeur avec les extr�mit�s en param�tres
	Bounds(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
	//Constructeur par d�faut
	Bounds() {};
	//Destructeur
	~Bounds();
	//Calcule le point central de l'objet associé
	Vector3D getCenter();

};

#endif