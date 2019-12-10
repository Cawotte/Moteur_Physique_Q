#include "Box.h"

// R�le : Constructeur - Initialise l'objet en faisant appel au constructeur de RigidBody dont h�rite la classe Box
// Entr�es : la masse, le vecteur position, le quaternion d'orientation, les dampings lin�aires et angulaires et les demi-dimensions de la boite
// Sortie : Aucune
Box::Box(float mass, Vector3D position, Quaternion orientation, float linearDamping, float angularDamping, float dx, float dy, float dz)
	:RigidBody(mass, position, orientation, linearDamping, angularDamping), dx_(dx), dy_(dy), dz_(dz)
{
}

// R�le : Destructeur - D�truit l'objet
// Entr�es : Aucune
// Sortie : Aucune
Box::~Box()
{
}

// R�le : Calcule la matrice de transformation et l'inverse du moment d'inertie de l'objet associ�
// Entr�es : Aucune
// Sortie : Aucune
void Box::calculDonneesDerivees() {

	//Calcul de transformMatrix : la matrice de transformation, en convertissant le quaternion d'orientation en Matrix3
	transformMatrix_ = orientation_.toMatrix3();

	//Calcul de I^-1 dans le repere du monde
	float data[] = { dy_ * dy_ + dz_ * dz_, 0, 0, 0, dx_*dx_ + dz_ * dz_, 0, 0, 0, dx_*dx_ + dy_ * dy_ };
	//cr�ation de la Matrix3 pour une boite rectangulaire
	Matrix3 I(data);
	I = I * (1 / (3 * inverseMass_));
	//Inversion et changement de base
	inverseInertiaTensor_ = I.inv().changeBase(transformMatrix_);

}

// R�le : Appelle la fonction de GluUtils qui dessine la boite selon ses demi-dimensions et sa couleur sur l'�cran
// Entr�es : Aucune
// Sortie : Aucune
void Box::display() {
	GlutUtils::drawRectangle(getPosition(), getOrientation(), dx_, dy_, dz_, color_);
}