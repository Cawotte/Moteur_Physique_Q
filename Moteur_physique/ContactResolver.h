#ifndef CONTACT_RESOLVER_H
#define CONTACT_RESOLVER_H

#include <list>

#include "Octree.h"
#include "Primitive.h"

class ContactResolver
{

private:

	Octree tree_ = Octree(0, Bounds(-1, 40, -1, 40, -1, 40));//arbre servant à la broad phase pour les collisions
	list<Primitive*> primitives_;//liste des primitives des objets étant sur scène
	vector<pair<Primitive*, Primitive*>> paires_;//liste des paires de primitives à tester pour la collision, issue de la broad phase

	int numCollisions_ = 0;

public:

	ContactResolver();
	~ContactResolver();

	void setNumCollisions(int num) { numCollisions_ = num; }

	int getNumCollisions() { return numCollisions_; }

	list<Primitive*> getPrimitives() { return primitives_; }

	void broadPhase();

	void displayBroadPhase();

	int narrowPhase();

	void addPrimitive(Primitive* p);

	bool hasCollision(Primitive* a, Primitive* b);

	void clear();
};

#endif