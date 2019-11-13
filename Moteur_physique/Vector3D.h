#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include "Matrix3.h"

using namespace std;

//Pour �viter des r�f�rences circulaires, on les d�clare ici.
class Matrix4;

// Classe permettant de manipuler les vecteurs 3D
class Vector3D
{
public:
	
	//coordonn�es
	float x;
	float y;
	float z;

	//constructors
	Vector3D();//vecteur nul
	Vector3D(float x, float y, float z);//vecteur initialis� avec les valeurs en param�tre

	~Vector3D();

	//Surcharges Op�rateurs
	Vector3D operator+(const Vector3D& b);//addition avec un autre vecteur 3
	Vector3D operator-(const Vector3D& b);//soustraction avec un autre vecteur 3
	Vector3D operator*(const float& lambda);//multiplication du vecteur par un scalaire

	//Op�rations
	Vector3D componentMult (Vector3D v);//produit des composantes avec un autre vecteur 3
	float dotProd(Vector3D v);//produit scalaire avec un autre vecteur 3
	Vector3D crossProd(Vector3D v);//produit vectoriel avec un autre vecteur 3 
	float tripleProd(Vector3D u, Vector3D v);//produit mixte avec deux autres vecteurs 3 : this.(u^v)
	float norm();//norme du vecteur
	Vector3D normalized();//normalise le vecteur

	Vector3D multiply(Matrix3 mat);//effectue le produit mat * this

	float distanceWith(Vector3D other);//calcule la distance avec un autre vecteur 3

	//Rep�res
	Vector3D fromLocalToWorld(Matrix3 transMatrix) { return multiply(transMatrix); }
	Vector3D fromWorldToLocal(Matrix3 transMatrix) { return multiply(transMatrix.inv()); }

	//affichage du vecteur pour le debug
	void display();
};

#endif