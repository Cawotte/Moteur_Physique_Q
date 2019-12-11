#include "Vector3D.h"

#include <cmath>

// R�le : Constructeur par d�faut - Vecteur nul
// Entr�es : Aucune
// Sortie : Aucune
Vector3D::Vector3D() : x(0), y(0), z(0)
{
}

// R�le : Constructeur - Initialise avec les valeurs en param�tres
// Entr�es : Coordonn�es d'initialisation
// Sortie : Aucune
Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
{
}

// R�le : Destructeur
// Entr�es : Aucune
// Sortie : Aucune
Vector3D::~Vector3D()
{
}


#pragma region Surcharge Op�rateurs
// R�le : Addition avec un autre vecteur 3
// Entr�es : L'autre vecteur
// Sortie : Le vecteur r�sultat
Vector3D Vector3D::operator+(const Vector3D& b) {
	Vector3D result(x + b.x, y + b.y, z + b.z);
	return result;
}

// R�le : Soustraction avec un autre vecteur 3
// Entr�es : L'autre vecteur
// Sortie : Le vecteur r�sultat
Vector3D Vector3D::operator-(const Vector3D& b) {
	Vector3D result(x - b.x, y - b.y, z - b.z);
	return result;
}

// R�le : Multiplication par un scalaire
// Entr�es : Le scalaire
// Sortie : Le vecteur r�sultat
Vector3D Vector3D::operator*(const float& lambda) {
	Vector3D result(lambda * x, lambda * y, lambda * z);
	return result;
}
#pragma endregion

#pragma region Op�rations
// R�le : Calcule le produit des composantes avec un autre vecteur 3
// Entr�es : L'autre vecteur
// Sortie : Le vecteur r�sultat
Vector3D Vector3D::componentMult(Vector3D v)
{
	Vector3D result(x * v.x, y * v.y, z * v.z);
	return result;
}

// R�le : Calcule le produit scalaire avec un autre vecteur 3
// Entr�es : L'autre vecteur
// Sortie : Le produit scalaire
float Vector3D::dotProd(Vector3D v)
{
	float result = x * v.x + y * v.y + z * v.z;
	return result;
}

// R�le : Calcule le produit vectoriel avec un autre vecteur 3 
// Entr�es : L'autre vecteur
// Sortie : Le produit vectoriel
Vector3D Vector3D::crossProd(Vector3D v)
{
	Vector3D result(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	return result;
}

// R�le : Calcule le produit mixte avec deux autres vecteurs 3 : this.(u^v)
// Entr�es : Les deux autres vecteurs
// Sortie : Le produit mixte
float Vector3D::tripleProd(Vector3D u, Vector3D v)
{
	return this->dotProd(u.crossProd(v));
}

// R�le : Calcule la norme du vecteur
// Entr�es : Aucune
// Sortie : La norme
float Vector3D::norm() {
	return sqrt(x * x + y * y + z * z);
}

// R�le : Normalise le vecteur
// Entr�es : Aucune
// Sortie : Le vecteur normalis�
Vector3D Vector3D::normalized() {
	return *this * (float)(1. / this->norm());
}

// R�le : Calcule la distance avec un autre vecteur 3
// Entr�es : L'autre vecteur
// Sortie : La distance
float Vector3D::distanceWith(Vector3D other) {	
	return sqrt(
		pow(this->x - other.x, 2.f) +
		pow(this->y - other.y, 2.f) +
		pow(this->z - other.z, 2.f)
		);
}

// R�le : Effectue le produit avec une matrice 3*3
// Entr�es : La matrice
// Sortie : Le vecteur r�sultat
Vector3D Vector3D::multiply(Matrix3 mat) {
	Vector3D result;
	//Pour chaque coordonn�e du vecteur r�sultat, on additionne les produits des cases adapt�es de la matrice et du vecteur multiplicateur
	result.x = mat.data_[0] * x + mat.data_[1] * y + mat.data_[2] * z;
	result.y = mat.data_[3] * x + mat.data_[4] * y + mat.data_[5] * z;
	result.z = mat.data_[6] * x + mat.data_[7] * y + mat.data_[8] * z;
	return result;
}

#pragma endregion

// R�le : Affiche sous la forme	(x, y, z)
// Entr�es : Aucune
// Sortie : Aucune
void Vector3D::display()
{
	cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}
