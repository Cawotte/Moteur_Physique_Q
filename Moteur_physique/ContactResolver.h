#ifndef CONTACT_RESOLVER_H
#define CONTACT_RESOLVER_H

#include <list>

#include "Octree.h"
#include "Primitive.h"
#include "Wall.h"

class ContactResolver
{

private:

	Octree tree_ = Octree(0, Bounds(-1, 40, -1, 40, -1, 40));//arbre servant à la broad phase pour les collisions
	list<Primitive*> primitives_;//liste des primitives des objets étant sur scène
	vector<pair<Primitive*, Primitive*>> paires_;//liste des paires de primitives à tester pour la collision, issue de la broad phase

public:

	ContactResolver();
	~ContactResolver();

	void broadPhase();

	void displayBroadPhase();

	void narrowPhase();

	void addPrimitive(Primitive* p);

	bool hasCollision(Primitive* a, Primitive* b);

	void clear();
};

#endif