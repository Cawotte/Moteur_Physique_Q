#include "Vector3D.h"

#include <cmath>

Vector3D::Vector3D() : x(0), y(0), z(0)
{

}

Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
{

}

Vector3D::~Vector3D()
{

}


#pragma region Surcharge Opérateurs
Vector3D Vector3D::operator+(const Vector3D& b) {
	Vector3D result(x + b.x, y + b.y, z + b.z);
	return result;
}

Vector3D Vector3D::operator-(const Vector3D& b) {
	Vector3D result(x - b.x, y - b.y, z - b.z);
	return result;
}

Vector3D Vector3D::operator*(const float& lambda) {
	Vector3D result(lambda * x, lambda * y, lambda * z);
	return result;
}
#pragma endregion

#pragma region Opérations
Vector3D Vector3D::componentMult(Vector3D v)
{
	Vector3D result(x * v.x, y * v.y, z * v.z);
	return result;
}

float Vector3D::dotProd(Vector3D v)
{
	float result = x * v.x + y * v.y + z * v.z;
	return result;
}

Vector3D Vector3D::crossProd(Vector3D v)
{
	Vector3D result(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	return result;
}

float Vector3D::tripleProd(Vector3D u, Vector3D v)
{
	return this->dotProd(u.crossProd(v));
}

float Vector3D::norm() {
	return sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalized() {
	return *this * (float)(1. / this->norm());
}


float Vector3D::distanceWith(Vector3D other) {
	
	return sqrt(
		pow(this->x - other.x, 2.f) +
		pow(this->y - other.y, 2.f) +
		pow(this->z - other.z, 2.f)
		);
}
#pragma endregion

void Vector3D::display()
{
	cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}
