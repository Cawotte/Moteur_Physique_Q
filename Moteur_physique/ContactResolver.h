#ifndef CONTACT_RESOLVER_H
#define CONTACT_RESOLVER_H

#include <list>

#include "Octree.h"
#include "Primitive.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : ContactResolver
// But : G�re la d�tection de collision entre les primitives qu'il contient
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ContactResolver
{

private:
	//Arbre servant � la broad phase pour les collisions
	Octree tree_ = Octree(0, Bounds(-1, 40, -1, 40, -1, 40));
	//Liste des primitives des objets �tant sur sc�ne
	list<Primitive*> primitives_;
	//Liste des paires de primitives � tester pour la collision, issue de la broad phase
	vector<pair<Primitive*, Primitive*>> paires_;
	//Nombre de collisions 
	int numCollisions_ = 0;

public:
	//Constructeur
	ContactResolver();
	//Destructeur
	~ContactResolver();
	//Setter du nombre de collisions
	void setNumCollisions(int num) { numCollisions_ = num; }
	//Getter du nombre de collisions
	int getNumCollisions() { return numCollisions_; }
	list<Primitive*> getPrimitives() { return primitives_; }
	//Effectue la broad phase
	void broadPhase();
	//Affiche le r�sultat de la broad phase
	void displayBroadPhase();
	//Effectue la narrow phase
	int narrowPhase();
	//Ajoute une primitive
	void addPrimitive(Primitive* p);
	//Teste si les deux primitives sont en collision
	bool hasCollision(Primitive* a, Primitive* b);
	//Vide les listes et l'arbre
	void clear();
};

#endif