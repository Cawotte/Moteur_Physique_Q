#include "Bounds.h"
  
// Rôle : Constructeur - Initialise l'objet en associant extrémités aux valeurs passées en paramètres
// Entrées : Valeurs des extrémités de l'objet associé
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


// Rôle : Constructeur par défaut - Initialise l'objet avec les valeurs par défaut indiquées dans le header
// Entrées : Aucune
// Sortie : Aucune
Bounds::~Bounds()
{
}

// Rôle : Calcule le point central de l'objet associé
// Entrées : Aucune
// Sortie : le Vector3 représentant le centre de l'objet associé
Vector3D Bounds::getCenter()
{
	//Point fictif représentant l'extrémité "basse" de l'objet
	Vector3D min = Vector3D{xmin_, ymin_, zmin_ };
	//Point fictif représentant l'extrémité "haute" de l'objet
	Vector3D max = Vector3D{xmax_, ymax_, zmax_ };
	//Calcule et retourne le point moyen entre les extrémités haute et basse : le point central de l
	return (min + max) * 0.5f;
}

