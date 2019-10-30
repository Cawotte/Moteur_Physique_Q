

#ifndef CONTACT
#define CONTACT

#include "Vector3D.h"

class Contact
{
public:
	bool hasContact_;
	float dPene_;
	Vector3D n_;

	Contact(float dPene, Vector3D n) : hasContact_(true), dPene_(dPene), n_(n) {

	}

	Contact() : hasContact_(false), dPene_(0), n_(Vector3D()) {

	}

	~Contact() {}

};

#endif

