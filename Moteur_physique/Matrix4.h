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
	float data_[12];//tableau de flottants représentant les 9 premières cases de la matrice 4*4, en lisant ligne par ligne
	//la dernière ligne est par défaut 0 0 0 1, donc non enregistrée à chaque fois
public:

	//Constructeurs
	Matrix4() {};//construit une matrice vide
	Matrix4(float data[12]);//construit une matrice contenant les valeurs passées dans le tableau en paramètre

	//Destructeur
	~Matrix4();

	////Surcharges Opérateurs
	//Somme
	Matrix4 operator+(const Matrix4& b);//fait la somme de la matrice avec une autre et renvoie le résultat
	//Produit Scalaire
	Matrix4 operator*(const float& lambda);//multiplie la matrice par un scalaire et renvoie le résultat
	//Produit Matriciel
	Matrix4 operator*(const Matrix4& b);//multiplie la matrice par une autre matrice 4*4 et renvoie le résultat
	//Produit avec Vector (if true then (x, y, z, 1) else (x, y, z, 0);
	Vector3D prodWithVec(const Vector3D& b, bool bo);//multiplie la matrice par un vecteur 3 et renvoie le résultat

	//Inverse
	Matrix4 inv();//calcule et renvoie l'inverse de la matrice

	//Transformation du vecteur de direction
	Vector3D transfoDir(Vector3D dir) {
		return prodWithVec(dir, false);
	}

	//Transformation inverse du vecteur de direction
	Vector3D transfoInvDir(Vector3D dir) {
		return (inv()).prodWithVec(dir, false);
	}

	//Fonction d'affichage pour les tests
	void display();
};

#endif