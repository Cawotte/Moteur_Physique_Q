#ifndef MATRIX3_H
#define MATRIX3_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Matrix3.h
// But : Represente une matrice 3 par 3 de reels et permet d'effectuer les operations suivantes:
//			- produit matriciel
//			- produit scalaire
//			- transposee
//			- matrice inverse
//			- changement de base
// Date de creation : 30/10/2019
// Derniere modification : 30/10/2019
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Vector3D.h"

class Matrix3
{
	float data_[9];

public:

	Matrix3() {};
	Matrix3(float data[9]);

	////Surcharges Opérateurs
	//Somme
	Matrix3 operator+(const Matrix3& b);
	//Produit Scalaire
	Matrix3 operator*(const float& lambda);
	//Produit Matriciel
	Matrix3 operator*(const Matrix3& b);
	//Produit avec Vector
	Vector3D operator*(const Vector3D& b);

	~Matrix3();
};

#endif