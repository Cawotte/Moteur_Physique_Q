#include "Matrix3.h"

Matrix3::Matrix3(float data[9]){
	for (int i = 0; i < 9; i++) {
		data_[i] = data[i];
	}
}


Matrix3::~Matrix3()
{
}

//Somme
Matrix3 Matrix3::operator+(const Matrix3& b) {
	Matrix3 result;
	for (int i = 0; i < 9; i++) {
		result.data_[i] = this->data_[i] + b.data_[i];
	}
	return result;
}

//Produit Scalaire
Matrix3 Matrix3::operator*(const float& lambda) {
	Matrix3 result;
	for (int i = 0; i < 9; i++) {
		result.data_[i] = this->data_[i] * lambda;
	}
	return result;
}

//Produit Matriciel
Matrix3 Matrix3::operator*(const Matrix3& b) {
	Matrix3 result;
	float temp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; i < 3; j++) {
			temp = 0;
			for (int k = 0; k < 3; k++) {
				temp += this->data_[3 * i + k] * b.data_[3 * k + j];
			}
			result.data_[3 * i + j] = temp;
		}
	}
	return result;
}

//Produit avec Vector
Vector3D Matrix3::operator*(const Vector3D& b) {
	Vector3D result;
	result.x = this->data_[0] * b.x + this->data_[1] * b.y + this->data_[2] * b.z;
	result.x = this->data_[3] * b.x + this->data_[4] * b.y + this->data_[5] * b.z;
	result.x = this->data_[6] * b.x + this->data_[7] * b.y + this->data_[8] * b.z;
	return result;
}