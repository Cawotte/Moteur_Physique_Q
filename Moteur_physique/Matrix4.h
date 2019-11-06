#ifndef MATRIX4_H
#define MATRIX4_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Matrix4.h
// But : Represente une matrice 4 par 4 de reels et permet d'effectuer les operations suivantes:
//			- produit matriciel
//			- produit scalaire
//			- matrice inverse
//			- changement de base
//		Cette representation omet la derniere ligne qui vaut toujours 0 0 0 1.
// Date de creation : 06/11/2019
// Derniere modification : 06/11/2019
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Vector3D.h"

#include <iostream>

class Matrix4
{
	float data_[12];
public:

	//Constructeurs
	Matrix4() {};
	Matrix4(float data[12]);

	//Destructeur
	~Matrix4();

	////Surcharges Opérateurs
	//Somme
	Matrix4 operator+(const Matrix4& b);
	//Produit Scalaire
	Matrix4 operator*(const float& lambda);
	//Produit Matriciel
	Matrix4 operator*(const Matrix4& b);
	//Produit avec Vector (if true then (x, y, z, 1) else (x, y, z, 0);
	Vector3D prodWithVec(const Vector3D& b, bool bo);

	//Inverse
	Matrix4 inv();

	//Fonction d'affichage pour les tests
	void display();
};

#endif