#include "Matrix4.h"

//Constructeur : copie le tableau pass� en param�tre dans celui membre de la classe
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
	//on parcourt les matrices en additionnant valeur � valeur
	for (int i = 0; i < 12; i++) {
		result.data_[i] = this->data_[i] + b.data_[i];
	}
	return result;
}

//Produit Scalaire
Matrix4 Matrix4::operator*(const float& lambda) {
	Matrix4 result;
	//on parcourt la matrice en multipliant � chaque fois par le scalaire en param�tre
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
	for (int i = 0; i < 3; i++) {//on parcourt les lignes de la matrice r�sultat
		//4 colonnes
		for (int j = 0; j < 4; j++) {//on parcourt les colonnes de la matrice r�sultat
			temp = 0;//la valeur de chaque case de la matrice r�sultat, 0 au d�part
			for (int k = 0; k < 3; k++) {//on parcourt les 3 premi�res cases de la ligne et la colonne concern�es des matrices multipli�es
				temp += this->data_[4 * i + k] * b.data_[4 * k + j];//on additionne le produit des cases point�es � la valeur de la case de la matrice r�sultat			
			}
			if (j == 3) {//Si derniere colonne uniquement alors on ajoute la derniere valeur car 4eme ligne : 0 0 0 1
				temp += this->data_[4 * i + j];
			}
			result.data_[4 * i + j] = temp;//on enregistre la valeur dans la case
		}
	}
	return result;
}

//Produit avec Vector (if true then (x, y, z, 1) else (x, y, z, 0);
Vector3D Matrix4::prodWithVec(const Vector3D& b, bool bo) {
	Vector3D result;
	//pour chaque coordonn�e du vecteur r�sultat, on additionne les produits des cases adapt�es de la matrice et du vecteur multiplicateur
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
	//calcul du d�terminant de la matrice
	float det = this->data_[0] * this->data_[5] * this->data_[10]
		+ this->data_[4] * this->data_[9] * this->data_[2]
		+ this->data_[8] * this->data_[1] * this->data_[6]
		- this->data_[0] * this->data_[9] * this->data_[6]
		- this->data_[4] * this->data_[1] * this->data_[10]
		- this->data_[8] * this->data_[5] * this->data_[2];
	if (det != 0) {//s'il n'est pas nul, c'est que la matrice est inversible : on calcule chacune des cases de la matrice r�sultat
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