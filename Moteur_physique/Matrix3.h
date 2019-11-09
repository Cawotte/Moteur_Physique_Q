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
	float data_[9];//tableau de flottants repr�sentant les 9 cases de la matrice 3*3, en lisant ligne par ligne

public:

	//Constructeurs
	Matrix3() {};//construit une matrice vide
	Matrix3(float data[9]);//construit une matrice contenant les valeurs pass�es dans le tableau en param�tre

	//Destructeur
	~Matrix3();

	////Surcharges Op�rateurs
	//Somme
	Matrix3 operator+(const Matrix3& b);//fait la somme de la matrice avec une autre et renvoie le r�sultat
	//Produit Scalaire
	Matrix3 operator*(const float& lambda);//multiplie la matrice par un scalaire et renvoie le r�sultat
	//Produit Matriciel
	Matrix3 operator*(const Matrix3& b);//multiplie la matrice par une autre matrice 3*3 et renvoie le r�sultat
	//Produit avec Vector
	Vector3D operator*(const Vector3D& b);//multiplie la matrice par un vecteur 3 et renvoie le r�sultat

	//Transposee
	Matrix3 transpo();//calcule et renvoie la transpos�e de la matrice

	//Inverse
	Matrix3 inv();//calcule et renvoie l'inverse de la matrice

	//Changement de base : change la matrice dans la base B et renvoie le r�sultat
	Matrix3 changeBase(Matrix3 B) {
		return (B * *this * B.inv());
	}

	//Fonction d'affichage pour les tests
	void display();

};

#endif