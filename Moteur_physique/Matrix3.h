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

#include <iostream>

class Matrix3
{
	float data_[9];

public:

	//Constructeurs
	Matrix3() {};
	Matrix3(float data[9]);

	//Destructeur
	~Matrix3();

	////Surcharges Opérateurs
	//Somme
	Matrix3 operator+(const Matrix3& b);
	//Produit Scalaire
	Matrix3 operator*(const float& lambda);
	//Produit Matriciel
	Matrix3 operator*(const Matrix3& b);
	//Produit avec Vector
	Vector3D operator*(const Vector3D& b);

	//Transposee
	Matrix3 transpo();

	//Inverse
	Matrix3 inv();

	//Changement de base

	Matrix3 changeBase(Matrix3 B) {
		return (B * *this * B.inv());
	}
	//Fonction d'affichage pour les tests
	void display();

};

#endif