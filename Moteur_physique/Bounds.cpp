#include "Bounds.h"
  
// R�le : Constructeur - Initialise l'objet en associant extr�mit�s aux valeurs pass�es en param�tres
// Entr�es : Valeurs des extr�mit�s de l'objet associ�
// Sortie : Aucune
Bounds::Bounds(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
	xmin_ = xmin;
	ymin_ = ymin;
	zmin_ = zmin;
	xmax_ = xmax;
	ymax_ = ymax;
	zmax_ = zmax;
	width_ = xmax_ - xmin_;
	height_ = ymax_ - ymin_;
	depth_ = zmax_ - zmin_;
}


// R�le : Constructeur par d�faut - Initialise l'objet avec les valeurs par d�faut indiqu�es dans le header
// Entr�es : Aucune
// Sortie : Aucune
Bounds::~Bounds()
{
}

Vector3D Bounds::getCenter()
{
	Vector3D min = Vector3D{xmin_, ymin_, zmin_ }; //p1
	Vector3D max = Vector3D{xmax_, ymax_, zmax_ }; //p1

	return (min + max) * 0.5f;
}

