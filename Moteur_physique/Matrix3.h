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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
class Vector3D;

class Matrix3
{

public:

	float data_[9];//tableau de flottants représentant les 9 cases de la matrice 3*3, en lisant ligne par ligne

	//Constructeurs
	Matrix3() {};//construit une matrice vide
	Matrix3(float data[9]);//construit une matrice contenant les valeurs passées dans le tableau en paramètre

	//Destructeur
	~Matrix3();

	////Surcharges Opérateurs
	//Somme
	Matrix3 operator+(const Matrix3& b);//fait la somme de la matrice avec une autre et renvoie le résultat
	//Produit Scalaire
	Matrix3 operator*(const float& lambda);//multiplie la matrice par un scalaire et renvoie le résultat
	//Produit Matriciel
	Matrix3 operator*(const Matrix3& b);//multiplie la matrice par une autre matrice 3*3 et renvoie le résultat
	//Produit avec Vector
	//Vector3D operator*(const Vector3D& b);//multiplie la matrice par un vecteur 3 et renvoie le résultat

	//Transposee
	Matrix3 transpo();//calcule et renvoie la transposée de la matrice

	//Inverse
	Matrix3 inv();//calcule et renvoie l'inverse de la matrice

	//Changement de base : change la matrice dans la base B et renvoie le résultat
	Matrix3 changeBase(Matrix3 B) {
		return (B * *this * B.inv());
	}
	
	//Retourne une matrice 4 par 4 avec pour derniere colonne et dernière ligne 0 0 0 1
	float* toMat44();

	//Fonction d'affichage pour les tests
	void display();

};

#endif