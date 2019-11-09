#include "Vector3D.h"

#include <cmath>

//construction d'un vecteur nul
Vector3D::Vector3D() : x(0), y(0), z(0)
{
}

//construction d'un vecteur avec les valeurs en param�tres
Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
{
}

//destructeur
Vector3D::~Vector3D()
{
}


#pragma region Surcharge Op�rateurs
//addition coordonn�e � coordonn�e avec un autre vecteur 3
Vector3D Vector3D::operator+(const Vector3D& b) {
	Vector3D result(x + b.x, y + b.y, z + b.z);
	return result;
}

//soustraction coordonn�e � coordonn�e avec un autre vecteur 3
Vector3D Vector3D::operator-(const Vector3D& b) {
	Vector3D result(x - b.x, y - b.y, z - b.z);
	return result;
}

//multiplication de chaque coordonn�e par un scalaire 
Vector3D Vector3D::operator*(const float& lambda) {
	Vector3D result(lambda * x, lambda * y, lambda * z);
	return result;
}
#pragma endregion

#pragma region Op�rations
//produit coordonn�e � coordonn�e avec un autre vecteur
Vector3D Vector3D::componentMult(Vector3D v)
{
	Vector3D result(x * v.x, y * v.y, z * v.z);
	return result;
}

//produit scalaire avec un autre vecteur 3 : somme des produits des coordonn�es
float Vector3D::dotProd(Vector3D v)
{
	float result = x * v.x + y * v.y + z * v.z;
	return result;
}

//produit vectoriel avec un autre vecteur 3 
Vector3D Vector3D::crossProd(Vector3D v)
{
	Vector3D result(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	return result;
}

//produit mixte avec deux autres vecteurs 3 : this.(u^v) : produit vectoriel entre les autres vecteurs, produit scalaire avec le r�sultat
float Vector3D::tripleProd(Vector3D u, Vector3D v)
{
	return this->dotProd(u.crossProd(v));
}

//norme du vecteur : racine carr� de la somme des carr�s des coordonn�es
float Vector3D::norm() {
	return sqrt(x * x + y * y + z * z);
}

//normalise le vecteur : le divise par sa norme pour passer celle-ci � 1
Vector3D Vector3D::normalized() {
	return *this * (float)(1. / this->norm());
}

//calcule la distance avec un autre vecteur 3 : racine carr�e de la somme des carr�s des diff�rences coordonn�e � coordonn�e
float Vector3D::distanceWith(Vector3D other) {	
	return sqrt(
		pow(this->x - other.x, 2.f) +
		pow(this->y - other.y, 2.f) +
		pow(this->z - other.z, 2.f)
		);
}
#pragma endregion

//Display
//Affiche le vecteur sous la forme
//	(x, y, z)
void Vector3D::display()
{
	cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}
