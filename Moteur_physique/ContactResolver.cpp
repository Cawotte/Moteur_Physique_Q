#include "ContactResolver.h"

ContactResolver::ContactResolver()
{
}

ContactResolver::~ContactResolver()
{
	clear();
}

void ContactResolver::resolveContacts(float t) {
	sortByAscendingVelocities();
	while (!contacts_.empty()) {
		contacts_.front()->resolve(t);
		deleteContact(contacts_.front());
		iterUsed_ += 1;
	}
}


void ContactResolver::sortByAscendingVelocities() {
	contacts_.sort([](ParticleContact* c1, ParticleContact* c2) {
		return c1->getVs() < c2->getVs();
	});
}


void ContactResolver::deleteContact(ParticleContact* paC) {
	contacts_.remove(paC);
	delete(paC);
}

void ContactResolver::clear() {
	while (!contacts_.empty()) {
		deleteContact(contacts_.front());
	}
}