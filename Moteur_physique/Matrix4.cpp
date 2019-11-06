#include "Matrix4.h"

//Constructeur
Matrix4::Matrix4(float data[12]) {
	for (int i = 0; i < 12; i++) {
		data_[i] = data[i];
	}
}

//Destructeur
Matrix4::~Matrix4()
{
}

//Somme
Matrix4 Matrix4::operator+(const Matrix4& b) {
	Matrix4 result;
	for (int i = 0; i < 12; i++) {
		result.data_[i] = this->data_[i] + b.data_[i];
	}
	return result;
}

//Produit Scalaire
Matrix4 Matrix4::operator*(const float& lambda) {
	Matrix4 result;
	for (int i = 0; i < 12; i++) {
		result.data_[i] = this->data_[i] * lambda;
	}
	return result;
}

//Produit Matriciel
Matrix4 Matrix4::operator*(const Matrix4& b) {
	Matrix4 result;
	float temp;
	//3 lignes
	for (int i = 0; i < 3; i++) {
		//4 colonnes
		for (int j = 0; j < 4; j++) {
			temp = 0;
			for (int k = 0; k < 3; k++) {
				temp += this->data_[4 * i + k] * b.data_[4 * k + j];
				//Si derniere colonne alors on ajoute la derniere valeur
			}
			if (j == 3) {
				temp += this->data_[4 * i + j];
			}
			result.data_[4 * i + j] = temp;
		}
	}
	return result;
}

//Produit avec Vector (if true then (x, y, z, 1) else (x, y, z, 0);
Vector3D Matrix4::prodWithVec(const Vector3D& b, bool bo) {
	Vector3D result;
	result.x = this->data_[0] * b.x + this->data_[1] * b.y + this->data_[2] * b.z;
	result.y = this->data_[4] * b.x + this->data_[5] * b.y + this->data_[6] * b.z;
	result.z = this->data_[8] * b.x + this->data_[9] * b.y + this->data_[10] * b.z;
	if (bo) {
		result.x += this->data_[3];
		result.y += this->data_[7];
		result.z += this->data_[11];
	}
	return result;
}

//Inverse
Matrix4 Matrix4::inv() {
	Matrix4 result;
	float det = this->data_[0] * this->data_[5] * this->data_[10]
		+ this->data_[4] * this->data_[9] * this->data_[2]
		+ this->data_[8] * this->data_[1] * this->data_[6]
		- this->data_[0] * this->data_[9] * this->data_[6]
		- this->data_[4] * this->data_[1] * this->data_[10]
		- this->data_[8] * this->data_[5] * this->data_[2];
	if (det != 0) {
		result.data_[0] = this->data_[5] * this->data_[10] - this->data_[9] * this->data_[6];
		result.data_[1] = this->data_[2] * this->data_[9] - this->data_[1] * this->data_[10];
		result.data_[2] = this->data_[1] * this->data_[6] - this->data_[2] * this->data_[5];
		result.data_[4] = this->data_[8] * this->data_[6] - this->data_[4] * this->data_[10];
		result.data_[5] = this->data_[0] * this->data_[10] - this->data_[2] * this->data_[8];
		result.data_[6] = this->data_[2] * this->data_[4] - this->data_[0] * this->data_[6];
		result.data_[8] = this->data_[4] * this->data_[8] - this->data_[8] * this->data_[5];
		result.data_[9] = this->data_[1] * this->data_[8] - this->data_[0] * this->data_[9];
		result.data_[10] = this->data_[0] * this->data_[5] - this->data_[1] * this->data_[4];
		result.data_[3] = this->data_[6] * this->data_[3] * this->data_[9]
			+ this->data_[1] * this->data_[7] * this->data_[10]
			+ this->data_[2] * this->data_[5] * this->data_[11]
			- this->data_[3] * this->data_[5] * this->data_[10]
			- this->data_[2] * this->data_[7] * this->data_[9]
			- this->data_[1] * this->data_[6] * this->data_[11];
		result.data_[7] = this->data_[4] * this->data_[3] * this->data_[10]
			+ this->data_[2] * this->data_[7] * this->data_[8]
			+ this->data_[0] * this->data_[6] * this->data_[11]
			- this->data_[3] * this->data_[6] * this->data_[8]
			- this->data_[0] * this->data_[7] * this->data_[10]
			- this->data_[4] * this->data_[2] * this->data_[11];
		result.data_[11] = this->data_[5] * this->data_[3] * this->data_[8]
			+ this->data_[0] * this->data_[7] * this->data_[9]
			+ this->data_[1] * this->data_[4] * this->data_[11]
			- this->data_[3] * this->data_[4] * this->data_[9]
			- this->data_[1] * this->data_[7] * this->data_[8]
			- this->data_[0] * this->data_[5] * this->data_[11];
		result = result * (1 / det);
	}
	return result;
}

//Display
//Affiche la matrice sous la forme
//	a b c d
//	e f g h
//	i j k l
void Matrix4::display() {
	std::cout << this->data_[0] << " " << this->data_[1] << " " << this->data_[2] << " " << this->data_[3] << endl;
	std::cout << this->data_[4] << " " << this->data_[5] << " " << this->data_[6] << " " << this->data_[7] << endl;
	std::cout << this->data_[8] << " " << this->data_[9] << " " << this->data_[10] << " " << this->data_[11] << endl;
}