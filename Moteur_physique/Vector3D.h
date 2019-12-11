#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include "Matrix3.h"

using namespace std;

//Pour éviter des références circulaires, on les déclare ici.
class Matrix4;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Vector3D
// But : Permet de manipuler des vecteurs 3D
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Vector3D
{
public:
	
	//Coordonnées
	float x;
	float y;
	float z;

	//Constructeur par défaut initialisant avec des valeurs par défaut (vecteur nul)
	Vector3D();
	//Constructeur initialisant avec les valeurs passées en paramètres
	Vector3D(float x, float y, float z);
	//Destructeur
	~Vector3D();

	//Surcharges Opérateurs
	//Addition avec un autre vecteur 3
	Vector3D operator+(const Vector3D& b);
	//Soustraction avec un autre vecteur 3
	Vector3D operator-(const Vector3D& b);
	//Multiplication du vecteur par un scalaire
	Vector3D operator*(const float& lambda);

	//Opérations
	//Calcule le produit des composantes avec un autre vecteur 3
	Vector3D componentMult (Vector3D v);
	//Calcule le produit scalaire avec un autre vecteur 3
	float dotProd(Vector3D v);
	//Calcule le produit vectoriel avec un autre vecteur 3 
	Vector3D crossProd(Vector3D v);
	//Calcule le produit mixte avec deux autres vecteurs 3 : this.(u^v)
	float tripleProd(Vector3D u, Vector3D v);
	//Calcule la norme du vecteur
	float norm();
	//Normalise le vecteur
	Vector3D normalized();
	//Effectue le produit avec une matrice 3*3
	Vector3D multiply(Matrix3 mat);
	//Calcule la distance avec un autre vecteur 3
	float distanceWith(Vector3D other);

	//Changent de repères
	Vector3D fromLocalToWorld(Matrix3 transMatrix) { return multiply(transMatrix); }
	Vector3D fromWorldToLocal(Matrix3 transMatrix) { return multiply(transMatrix.inv()); }

	//Affiche le vecteur pour le debug
	void display();
};

#endif