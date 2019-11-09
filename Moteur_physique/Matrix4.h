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
	float data_[12];//tableau de flottants repr�sentant les 9 premi�res cases de la matrice 4*4, en lisant ligne par ligne
	//la derni�re ligne est par d�faut 0 0 0 1, donc non enregistr�e � chaque fois
public:

	//Constructeurs
	Matrix4() {};//construit une matrice vide
	Matrix4(float data[12]);//construit une matrice contenant les valeurs pass�es dans le tableau en param�tre

	//Destructeur
	~Matrix4();

	////Surcharges Op�rateurs
	//Somme
	Matrix4 operator+(const Matrix4& b);//fait la somme de la matrice avec une autre et renvoie le r�sultat
	//Produit Scalaire
	Matrix4 operator*(const float& lambda);//multiplie la matrice par un scalaire et renvoie le r�sultat
	//Produit Matriciel
	Matrix4 operator*(const Matrix4& b);//multiplie la matrice par une autre matrice 4*4 et renvoie le r�sultat
	//Produit avec Vector (if true then (x, y, z, 1) else (x, y, z, 0);
	Vector3D prodWithVec(const Vector3D& b, bool bo);//multiplie la matrice par un vecteur 3 et renvoie le r�sultat

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