#ifndef CONTACT_RESOLVER
#define CONTACT_RESOLVER

#include <list>

#include "ParticleContact.h"

class ContactResolver
{
private:

	list<ParticleContact*> contacts_;
	int iter_ = 0;
	int iterUsed_ = 0;

public:

	ContactResolver();
	~ContactResolver();

	void setIter(int iter) { iter_ = iter; }

	void resolveContacts(float t);

	void sortByAscendingVelocities();

	void addContact(ParticleContact* paC) { contacts_.push_front(paC); }
	void deleteContact(ParticleContact* paC);

	bool limitNotReached() { return (!contacts_.empty() && iterUsed_ < iter_); }
	void limitReached() { iterUsed_ = 0; }

	void clear();
};


#endif