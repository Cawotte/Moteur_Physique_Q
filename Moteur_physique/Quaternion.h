
#ifndef QUATERNION
#define QUATERNION

#include "Vector3D.h"
#include "Matrix3.h"

class Quaternion
{

public:
	float r_, i_, j_, k_;

	Quaternion(float r, float i, float j, float k) :
		r_(r), i_(i), j_(j), k_(k)
	{

	}

	//Normalize le Quaternion (norme à 1)
	void normalize();

	//Multiplicateur de Quaternions
	void operator*=(const Quaternion& q);
	Quaternion operator*(const Quaternion& q);

	//Multiplicateur par scalaire
	Quaternion operator*(const float& f); 

	//Additions de Quaternion
	void operator+=(const Quaternion& q);
	Quaternion operator+(const Quaternion& q);

	//Applique la rotation angulaire au Quaternion.
	void rotate(Vector3D vec);

	//Mets à jour l'orientation du Quaternion en fonction d'une vélocité angulaire et de delta T
	void updateAngularVelocity(Vector3D vec, float timeElapsed);

	//Convertie le Quaternion en la Matrix3 correspondante.
	Matrix3 toMatrix3();

	void print();
};

#endif

