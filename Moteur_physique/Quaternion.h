
#ifndef QUATERNION
#define QUATERNION

#include "Vector3D.h"

class Quaternion
{

public:
	float r_, i_, j_, k_;

	Quaternion(float r, float i, float j, float k) :
		r_(r), i_(i), j_(j), k_(k)
	{

	}


	void normalize();

	void operator*=(const Quaternion& q);

	void rotate(Vector3D vec);
	void updateAngularVelocity(Vector3D vec, float timeElapsed);
};

#endif

