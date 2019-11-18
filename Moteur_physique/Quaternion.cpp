#include "Quaternion.h"

void Quaternion::normalize()
{
	float d = (r_ * r_) + (i_ * i_) + (j_ * j_) + (k_ * k_);

	if (d == 0.f) {
		r_ = 1;
	}
	else {
		d = 1 / sqrtf(d);

		r_ *= d;
		i_ *= d;
		j_ *= d;
		k_ *= d;
	}

}

void Quaternion::operator*=(const Quaternion& q)
{
	*this = *this * q;
}

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

Quaternion Quaternion::operator*(const float& f)
{
	return Quaternion{
		r_ * f,

		i_ * f,

		j_ * f,

		k_ * f
	};

}

void Quaternion::operator+=(const Quaternion& q)
{
	*this = *this + q;
}

Quaternion Quaternion::operator+(const Quaternion& q)
{
	return Quaternion{
		r_ + q.r_,
		i_ + q.i_,
		j_ + q.j_,
		k_ + q.k_,
	};
}

void Quaternion::rotate(Vector3D vec)
{
	Quaternion q{0, vec.x, vec.y, vec.z };

	*this *= q; //change the value of that object with the result
}

void Quaternion::updateAngularVelocity(Vector3D vec, float timeElapsed)
{
	//turn the Vector3D into a quaternion
	Quaternion w{ 0, vec.x, vec.y, vec.z };

	// O1' = O1 + dT/2f * w1 * O1;

	Quaternion thetaPrime = *this + (w * (timeElapsed / 2.f)) * *this;
	*this = thetaPrime;
	

}

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

Matrix4 Quaternion::toMatrix4()
{
	float data[12] = {
		1.f - (2 * j_ * j_ + 2 * k_ * k_),
		2 * i_ * j_ + 2 * k_ * r_,
		2 * i_ * k_ - 2 * j_ * r_,
		i_, //New line for Matrix4

		2 * i_ * j_ - 2 * k_ * r_,
		1 - (2 * i_ * i_ + 2 * k_ * k_),
		2 * j_ * k_ + 2 * i_ * r_,
		j_, //New line for Matrix4

		2 * i_ * k_ + 2 * j_ * r_,
		2 * j_ * k_ - 2 * i_ * r_,
		1 - (2 * i_ * i_ + 2 * j_ * j_),
		k_ //New line for Matrix4
	};

	return Matrix4{ data };
}

void Quaternion::toEulerAngles(float& xAngle, float& yAngle, float& zAngle)
{
	xAngle = atanf( (2.f * (r_ * i_ + j_ * k_)) / ( 1.f - 2 * (i_ * i_ + j_ * j_)));

	yAngle = asinf(2.f * (r_ * j_ - k_ * i_));

	zAngle = atanf((2.f * (r_ * k_ + i_ * j_)) / (1.f - 2 * (j_ * j_ + k_ * k_)));
}

void Quaternion::toAngleAndAxes(float& normAngle, Vector3D& n) {
	normAngle = 2 * acos(r_);
	n.x = i_ / sin(normAngle / 2);
	n.y = j_ / sin(normAngle / 2);
	n.z = k_ / sin(normAngle / 2);
}

void Quaternion::print()
{
	cout << "(" << r_ << ", " << i_ << ", " << j_ << ", " << k_ << ")";
}
