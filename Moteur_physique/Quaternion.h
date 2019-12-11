
#ifndef QUATERNION
#define QUATERNION

#include "Vector3D.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include <cmath>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Quaternion
// But : Repr�sente un Quaternion
//		 Permet les calculs sur un Quaternion
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Quaternion
{

public:
	//Coordonn�es du Quaternion
	float r_, i_, j_, k_;
	//Constructeur par d�faut avec valeurs par d�faut
	Quaternion() :r_(0), i_(0), j_(0), k_(1) {}
	//Constructeur permettant d'initialiser les coordonn�es
	Quaternion(float r, float i, float j, float k) :
		r_(r), i_(i), j_(j), k_(k){}

	//Normalise le Quaternion (norme � 1)
	void normalize();

	//Multiplicateur de Quaternions
	void operator*=(const Quaternion& q);
	Quaternion operator*(const Quaternion& q);

	//Multiplicateur par scalaire
	Quaternion operator*(const float& f); 

	//Additions de Quaternion
	void operator+=(const Quaternion& q);
	Quaternion operator+(const Quaternion& q);

	//Applique la rotation angulaire au Quaternion
	void rotate(Vector3D vec);

	//Met � jour l'orientation du Quaternion en fonction d'une v�locit� angulaire et de delta T
	void updateAngularVelocity(Vector3D vec, float timeElapsed);

	//Convertit le Quaternion en la Matrix3/4 correspondante. (SetOrientation)
	Matrix3 toMatrix3();
	Matrix4 toMatrix4();

	//Convertit en angles d'Euler
	void toEulerAngles(float& xAngle, float& yAngle, float& zAngle);
	//Affiche
	void print();
};

#endif

