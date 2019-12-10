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

// R�le : Calcule le point central de l'objet associ�
// Entr�es : Aucune
// Sortie : le Vector3 repr�sentant le centre de l'objet associ�
Vector3D Bounds::getCenter()
{
	//Point fictif repr�sentant l'extr�mit� "basse" de l'objet
	Vector3D min = Vector3D{xmin_, ymin_, zmin_ };
	//Point fictif repr�sentant l'extr�mit� "haute" de l'objet
	Vector3D max = Vector3D{xmax_, ymax_, zmax_ };
	//Calcule et retourne le point moyen entre les extr�mit�s haute et basse : le point central de l
	return (min + max) * 0.5f;
}

