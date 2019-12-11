#include "Quaternion.h"

// R�le : Normalise le Quaternion (norme � 1)
// Entr�es : Aucune
// Sortie : Aucune
void Quaternion::normalize()
{
	float d = (r_ * r_) + (i_ * i_) + (j_ * j_) + (k_ * k_);

	if (d == 0.f) {
		r_ = 1;
	}
	else 
	{
		d = 1 / sqrtf(d);

		r_ *= d;
		i_ *= d;
		j_ *= d;
		k_ *= d;
	}

}

// R�le : Surcharge de l'op�rateur *= entre deux quaternions, stocke dans this
// Entr�es : Quaternion avec lequel multiplier
// Sortie : Aucune
void Quaternion::operator*=(const Quaternion& q)
{
	*this = *this * q;
}

// R�le : Surcharge de l'op�rateur * entre deux quaternions
// Entr�es : Aucune
// Sortie : Le quaternion calcul�
Quaternion Quaternion::operator*(const Quaternion& q)
{
	return Quaternion{
		r_ * q.r_ -
		i_ * q.i_ -
		j_ * q.j_ -
		k_ * q.k_,

		r_ * q.i_ +
		i_ * q.r_ +
		j_ * q.k_ -
		k_ * q.j_,

		r_ * q.j_ +
		j_ * q.r_ +
		k_ * q.i_ -
		i_ * q.k_,

		r_ * q.k_ +
		k_ * q.r_ +
		i_ * q.j_ -
		j_ * q.i_
	};

}

// R�le : Surcharge de l'op�rateur * avec un scalaire
// Entr�es : Aucune
// Sortie : Le quaternion calcul�
Quaternion Quaternion::operator*(const float& f)
{
	return Quaternion{
		r_ * f,

		i_ * f,

		j_ * f,

		k_ * f
	};

}

// R�le : Surcharge de l'op�rateur += entre deux quaternions, stocke le r�sultat dans this
// Entr�es : Aucune
// Sortie : Aucune
void Quaternion::operator+=(const Quaternion& q)
{
	*this = *this + q;
}

// R�le : Surcharge de l'op�rateur += entre deux quaternions
// Entr�es : Aucune
// Sortie : Le Quaternion calcul�
Quaternion Quaternion::operator+(const Quaternion& q)
{
	return Quaternion{
		r_ + q.r_,
		i_ + q.i_,
		j_ + q.j_,
		k_ + q.k_,
	};
}

// R�le : Applique la rotation angulaire au Quaternion
// Entr�es : Rotation angulaire
// Sortie : Aucune
void Quaternion::rotate(Vector3D vec)
{
	Quaternion q{0, vec.x, vec.y, vec.z };

	*this *= q; //change la valeur de this avec le r�sultat
}

// R�le : Met � jour l'orientation du Quaternion en fonction d'une v�locit� angulaire et de delta T
// Entr�es : V�locit� angulaire et delta T
// Sortie : Aucune
void Quaternion::updateAngularVelocity(Vector3D vec, float timeElapsed)
{
	//transforme le vecteur en Quaternion
	Quaternion w{ 0, vec.x, vec.y, vec.z };

	// O1' = O1 + dT/2f * w1 * O1;

	Quaternion thetaPrime = *this + (w * (timeElapsed / 2.f)) * *this;
	thetaPrime.normalize();
	*this = thetaPrime;
	

}

// R�le : Convertit le Quaternion en Matrix3
// Entr�es : Aucune
// Sortie : Matrice correspondante
Matrix3 Quaternion::toMatrix3()
{
	float data[9] = {
		1.f - (2 * j_ * j_ + 2 * k_ * k_), 
		2 * i_ * j_ + 2 * k_ * r_,
		2 * i_ * k_ - 2 * j_ * r_,

		2 * i_ * j_ - 2 * k_ * r_,
		1 - (2 * i_ * i_ + 2 * k_ * k_),
		2 * j_ * k_ + 2 * i_ * r_,

		2 * i_ * k_ + 2 * j_ * r_,
		2 * j_ * k_ - 2 * i_ * r_,
		1 -(2 * i_ * i_ + 2 * j_ * j_)
	};

	return Matrix3{data};
}

// R�le : Convertit le Quaternion en Matrix4
// Entr�es : Aucune
// Sortie : Matrice 4
Matrix4 Quaternion::toMatrix4()
{
	float data[12] = {
		1.f - (2 * j_ * j_ + 2 * k_ * k_),
		2 * i_ * j_ + 2 * k_ * r_,
		2 * i_ * k_ - 2 * j_ * r_,
		i_, //Nouvelle ligne pour Matrix4

		2 * i_ * j_ - 2 * k_ * r_,
		1 - (2 * i_ * i_ + 2 * k_ * k_),
		2 * j_ * k_ + 2 * i_ * r_,
		j_, //Nouvelle ligne pour Matrix4

		2 * i_ * k_ + 2 * j_ * r_,
		2 * j_ * k_ - 2 * i_ * r_,
		1 - (2 * i_ * i_ + 2 * j_ * j_),
		k_ //Nouvelle ligne pour Matrix4
	};

	return Matrix4{ data };
}

// R�le : Convertit en angles d'Euler
// Entr�es : Coordonn�es de l'angle
// Sortie : Aucune
void Quaternion::toEulerAngles(float& xAngle, float& yAngle, float& zAngle)
{
	xAngle = atanf( (2.f * (r_ * i_ + j_ * k_)) / ( 1.f - 2 * (i_ * i_ + j_ * j_)));

	yAngle = asinf(2.f * (r_ * j_ - k_ * i_));

	zAngle = atanf((2.f * (r_ * k_ + i_ * j_)) / (1.f - 2 * (j_ * j_ + k_ * k_)));
}

// R�le : Affiche
// Entr�es : Aucune
// Sortie : Aucune
void Quaternion::print()
{
	cout << "(" << r_ << ", " << i_ << ", " << j_ << ", " << k_ << ")" << endl;
}
