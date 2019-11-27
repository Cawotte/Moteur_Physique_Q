
#ifndef QUATERNION
#define QUATERNION

#include "Vector3D.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include <cmath>

class Quaternion
{

public:
	float r_, i_, j_, k_;

	Quaternion() :r_(0), i_(0), j_(0), k_(0) {}

	Quaternion(float r, float i, float j, float k) :
		r_(r), i_(i), j_(j), k_(k)
	{

	}

	//Normalize le Quaternion (norme � 1)
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

	//Mets � jour l'orientation du Quaternion en fonction d'une v�locit� angulaire et de delta T
	void updateAngularVelocity(Vector3D vec, float timeElapsed);

	//Convertie le Quaternion en la Matrix3/4 correspondante. (SetOrientation)
	Matrix3 toMatrix3();
	Matrix4 toMatrix4();

	void toEulerAngles(float& xAngle, float& yAngle, float& zAngle);

	void print();
};

#endif

