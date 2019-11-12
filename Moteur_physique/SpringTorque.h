#ifndef SPRING_TORQUE
#define SPRING_TORQUE

#include "ForceGenerator.h"

class SpringTorque : public ForceGenerator
{

private:

	Vector3D p1_;
	Vector3D p2_;

	RigidBody otherBody_;

	float springCst_; //constante de ressort. (K?)
	float restLenght_; //Longueur au repos.

public:

	SpringTorque(Vector3D p1, Vector3D p2, RigidBody rb, float k, float restLenght) :
		p1_(p1), p2_(p2), otherBody_(rb), springCst_(k), restLenght_(restLenght) {

	}

	void updateForce(RigidBody* rb, float t);

};

#endif