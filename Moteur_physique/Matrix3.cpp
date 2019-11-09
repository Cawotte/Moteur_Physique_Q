#include "Matrix3.h"

//Constructeur : copie le tableau pass� en param�tre dans celui membre de la classe
Matrix3::Matrix3(float data[9]){
	for (int i = 0; i < 9; i++) {
		data_[i] = data[i];
	}
}

//Destructeur
Matrix3::~Matrix3()
{
}

//Somme
Matrix3 Matrix3::operator+(const Matrix3& b) {
	Matrix3 result;
	//on parcourt les matrices en additionnant valeur � valeur
	for (int i = 0; i < 9; i++) {
		result.data_[i] = this->data_[i] + b.data_[i];
	}
	return result;
}

//Produit Scalaire
Matrix3 Matrix3::operator*(const float& lambda) {
	Matrix3 result;
	//on parcourt la matrice en multipliant � chaque fois par le scalaire en param�tre
	for (int i = 0; i < 9; i++) {
		result.data_[i] = this->data_[i] * lambda;
	}
	return result;
}

//Produit Matriciel
Matrix3 Matrix3::operator*(const Matrix3& b) {
	Matrix3 result;
	float temp;
	for (int i = 0; i < 3; i++) {//on parcourt les lignes de la matrice r�sultat
		for (int j = 0; j < 3; j++) {//on parcourt les colonnes de la matrice r�sultat
			temp = 0;//la valeur de chaque case de la matrice r�sultat, 0 au d�part
			for (int k = 0; k < 3; k++) {//on parcourt la ligne et la colonne concern�es des matrices multipli�es
				temp += this->data_[3 * i + k] * b.data_[3 * k + j];//on additionne le produit des cases point�es � la valeur de la case de la matrice r�sultat
			}
			result.data_[3 * i + j] = temp;//on enregistre la valeur dans la case
		}
	}
	return result;
}

//Produit avec Vector
Vector3D Matrix3::operator*(const Vector3D& b) {
	Vector3D result;
	//pour chaque coordonn�e du vecteur r�sultat, on additionne les produits des cases adapt�es de la matrice et du vecteur multiplicateur
	result.x = this->data_[0] * b.x + this->data_[1] * b.y + this->data_[2] * b.z;
	result.y = this->data_[3] * b.x + this->data_[4] * b.y + this->data_[5] * b.z;
	result.z = this->data_[6] * b.x + this->data_[7] * b.y + this->data_[8] * b.z;
	return result;
}


//Transposee
Matrix3 Matrix3::transpo() {
	Matrix3 result;
	//on parcourt la matrice r�sultat
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.data_[3 * j + i] = this->data_[3 * i + j];//on associe � la case la valeur en sym�trique de la matrice originale
		}
	}
	return result;
}

//Inverse
Matrix3 Matrix3::inv() {
	Matrix3 result;
	//calcul du d�terminant de la matrice
	float det = this->data_[0] * this->data_[4] * this->data_[8]
		+ this->data_[3] * this->data_[7] * this->data_[2]
		+ this->data_[6] * this->data_[1] * this->data_[5]
		- this->data_[0] * this->data_[7] * this->data_[5]
		- this->data_[6] * this->data_[4] * this->data_[2]
		- this->data_[3] * this->data_[1] * this->data_[8];
	if (det != 0) {//s'il n'est pas nul, c'est que la matrice est inversible : on calcule chacune des cases de la matrice r�sultat
		result.data_[0] = this->data_[4] * this->data_[8] - this->data_[5] * this->data_[7];
		result.data_[1] = this->data_[2] * this->data_[7] - this->data_[1] * this->data_[8];
		result.data_[2] = this->data_[1] * this->data_[5] - this->data_[2] * this->data_[4];
		result.data_[3] = this->data_[5] * this->data_[6] - this->data_[3] * this->data_[8];
		result.data_[4] = this->data_[0] * this->data_[8] - this->data_[2] * this->data_[6];
		result.data_[5] = this->data_[2] * this->data_[3] - this->data_[0] * this->data_[5];
		result.data_[6] = this->data_[3] * this->data_[7] - this->data_[4] * this->data_[6];
		result.data_[7] = this->data_[1] * this->data_[6] - this->data_[0] * this->data_[7];
		result.data_[8] = this->data_[0] * this->data_[4] - this->data_[1] * this->data_[3];
		result = result * (1 / det);
	}
	return result;
}

//Display
//Affiche la matrice sous la forme
//	a b c
//	d e f
//	g h i
void Matrix3::display() {
	std::cout << this->data_[0] << " " << this->data_[1] << " " << this->data_[2] << endl;
	std::cout << this->data_[3] << " " << this->data_[4] << " " << this->data_[5] << endl;
	std::cout << this->data_[6] << " " << this->data_[7] << " " << this->data_[8] << endl;
}