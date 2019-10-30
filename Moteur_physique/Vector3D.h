#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

using namespace std;

// Classe permettant de manipuler les vecteurs 3D
class Vector3D
{
public:
	
	//position
	float x;
	float y;
	float z;

	//constructors
	Vector3D();
	Vector3D(float x, float y, float z);

	~Vector3D();

	//Surcharges Opérateurs
	Vector3D operator+(const Vector3D& b);
	Vector3D operator-(const Vector3D& b);
	Vector3D operator*(const float& lambda);

	//Opérations
	Vector3D componentMult (Vector3D v);//produit des composantes
	float dotProd(Vector3D v);//produit scalaire
	Vector3D crossProd(Vector3D v);//produit vectoriel
	float tripleProd(Vector3D u, Vector3D v);//produit mixte : this.(u^v)
	float norm();
	Vector3D normalized();

	float distanceWith(Vector3D other);

	//autre
	void display();
};

#endif