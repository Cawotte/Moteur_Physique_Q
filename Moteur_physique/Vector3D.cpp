#include "Vector3D.h"

#include <cmath>

// Rôle : Constructeur par défaut - Vecteur nul
// Entrées : Aucune
// Sortie : Aucune
Vector3D::Vector3D() : x(0), y(0), z(0)
{
}

// Rôle : Constructeur - Initialise avec les valeurs en paramètres
// Entrées : Coordonnées d'initialisation
// Sortie : Aucune
Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
{
}

// Rôle : Destructeur
// Entrées : Aucune
// Sortie : Aucune
Vector3D::~Vector3D()
{
}


#pragma region Surcharge Opérateurs
// Rôle : Addition avec un autre vecteur 3
// Entrées : L'autre vecteur
// Sortie : Le vecteur résultat
Vector3D Vector3D::operator+(const Vector3D& b) {
	Vector3D result(x + b.x, y + b.y, z + b.z);
	return result;
}

// Rôle : Soustraction avec un autre vecteur 3
// Entrées : L'autre vecteur
// Sortie : Le vecteur résultat
Vector3D Vector3D::operator-(const Vector3D& b) {
	Vector3D result(x - b.x, y - b.y, z - b.z);
	return result;
}

// Rôle : Multiplication par un scalaire
// Entrées : Le scalaire
// Sortie : Le vecteur résultat
Vector3D Vector3D::operator*(const float& lambda) {
	Vector3D result(lambda * x, lambda * y, lambda * z);
	return result;
}
#pragma endregion

#pragma region Opérations
// Rôle : Calcule le produit des composantes avec un autre vecteur 3
// Entrées : L'autre vecteur
// Sortie : Le vecteur résultat
Vector3D Vector3D::componentMult(Vector3D v)
{
	Vector3D result(x * v.x, y * v.y, z * v.z);
	return result;
}

// Rôle : Calcule le produit scalaire avec un autre vecteur 3
// Entrées : L'autre vecteur
// Sortie : Le produit scalaire
float Vector3D::dotProd(Vector3D v)
{
	float result = x * v.x + y * v.y + z * v.z;
	return result;
}

// Rôle : Calcule le produit vectoriel avec un autre vecteur 3 
// Entrées : L'autre vecteur
// Sortie : Le produit vectoriel
Vector3D Vector3D::crossProd(Vector3D v)
{
	Vector3D result(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	return result;
}

// Rôle : Calcule le produit mixte avec deux autres vecteurs 3 : this.(u^v)
// Entrées : Les deux autres vecteurs
// Sortie : Le produit mixte
float Vector3D::tripleProd(Vector3D u, Vector3D v)
{
	return this->dotProd(u.crossProd(v));
}

// Rôle : Calcule la norme du vecteur
// Entrées : Aucune
// Sortie : La norme
float Vector3D::norm() {
	return sqrt(x * x + y * y + z * z);
}

// Rôle : Normalise le vecteur
// Entrées : Aucune
// Sortie : Le vecteur normalisé
Vector3D Vector3D::normalized() {
	return *this * (float)(1. / this->norm());
}

// Rôle : Calcule la distance avec un autre vecteur 3
// Entrées : L'autre vecteur
// Sortie : La distance
float Vector3D::distanceWith(Vector3D other) {	
	return sqrt(
		pow(this->x - other.x, 2.f) +
		pow(this->y - other.y, 2.f) +
		pow(this->z - other.z, 2.f)
		);
}

// Rôle : Effectue le produit avec une matrice 3*3
// Entrées : La matrice
// Sortie : Le vecteur résultat
Vector3D Vector3D::multiply(Matrix3 mat) {
	Vector3D result;
	//Pour chaque coordonnée du vecteur résultat, on additionne les produits des cases adaptées de la matrice et du vecteur multiplicateur
	result.x = mat.data_[0] * x + mat.data_[1] * y + mat.data_[2] * z;
	result.y = mat.data_[3] * x + mat.data_[4] * y + mat.data_[5] * z;
	result.z = mat.data_[6] * x + mat.data_[7] * y + mat.data_[8] * z;
	return result;
}

#pragma endregion

// Rôle : Affiche sous la forme	(x, y, z)
// Entrées : Aucune
// Sortie : Aucune
void Vector3D::display()
{
	cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}
