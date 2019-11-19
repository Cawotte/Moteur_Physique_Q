#include "Box.h"

Box::Box(float mass, Vector3D position, Quaternion orientation, float linearDamping, float angularDamping, float dx, float dy, float dz)
	:RigidBody(mass, position, orientation, linearDamping, angularDamping), dx_(dx), dy_(dy), dz_(dz)
{
}

Box::~Box()
{
}

void Box::calculDonneesDerivees() {

	//Calcul de transformMatrix
	transformMatrix_ = orientation_.toMatrix3();

	//Calcul de I^-1 dans le repere du monde)
	float data[] = { dy_ * dy_ + dz_ * dz_, 0, 0, 0, dx_*dx_ + dz_ * dz_, 0, 0, 0, dx_*dx_ + dy_ * dy_ };
	Matrix3 I(data);
	I = I * (1 / (12 * inverseMass_));
	inverseInertiaTensor_ = I.inv().changeBase(transformMatrix_);

}

void Box::display() {
	GlutUtils::drawRectangle(getPosition(), getOrientation(), dx_, dy_, dz_, Color::blue);
}