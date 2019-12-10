#include "ContactResolver.h"


// Rôle : Constructeur par défaut - Initialise l'objet 
// Entrées : Aucune
// Sortie : Aucune
ContactResolver::ContactResolver()
{
}

// Rôle : Vide et détruit l'objet 
// Entrées : Aucune
// Sortie : Aucune
ContactResolver::~ContactResolver()
{
	clear();
}

// Rôle : Effectue la broad phase
// Entrées : Aucune
// Sortie : Aucune
void ContactResolver::broadPhase() {
	//Vide l'octree
	tree_.clear();
	//Ajoute chaque primitive dans l'octree
	std::list<Primitive*>::iterator it;
	for (it = primitives_.begin(); it != primitives_.end(); it++)
	{
		tree_.insert((*it));
	}
	//Vide la liste de paires
	paires_.clear();
	//Effectue le pairing
	tree_.pairing(paires_);
}

// Rôle : Affiche le résultat de la broad phase 
// Entrées : Aucune
// Sortie : Aucune
void ContactResolver::displayBroadPhase() {
	//Affiche l'octree
	tree_.display();
	//Affiche chaque paire calculée
	for (int k = 0; k < paires_.size(); k++)
	{
		cout << "paire numero " << k;
		cout << " (" << (paires_[k].first->bounds_.xmin_ + paires_[k].first->bounds_.xmax_) / 2 << " " << (paires_[k].first->bounds_.ymin_ + paires_[k].first->bounds_.ymax_) / 2 << " " << (paires_[k].first->bounds_.zmin_ + paires_[k].first->bounds_.zmax_) / 2 << ") ";
		cout << "(" << (paires_[k].second->bounds_.xmin_ + paires_[k].second->bounds_.xmax_) / 2 << " " << (paires_[k].second->bounds_.ymin_ + paires_[k].second->bounds_.ymax_) / 2 << " " << (paires_[k].second->bounds_.zmin_ + paires_[k].second->bounds_.zmax_) / 2 << ")" << endl;
	}
}

// Rôle : Effectue la narrow phase 
// Entrées : Aucune
// Sortie : Le nombre de collisions
int ContactResolver::narrowPhase() {
	int collisions = 0;
	//Pour chaque paire issue de la broad phase, teste la collision entre les deux
	std::vector<pair<Primitive*, Primitive*>>::iterator itp;
	for (itp = paires_.begin(); itp != paires_.end(); itp++)
	{
		Primitive* a = itp->first;
		Primitive* b = itp->second;
		if (hasCollision(a, b)) 
		{
			//S'il y a collision, augmente le compteur
			collisions += 1;
		}
	}
	return collisions;
}

// Rôle : Teste si les deux primitives sont en collision
// Entrées : Aucune
// Sortie : S'il y a collision
bool ContactResolver::hasCollision(Primitive* a, Primitive* b) {	

	return (a->isPrimitiveCollidingWith(b) || b->isPrimitiveCollidingWith(a));

}

// Rôle : Ajoute une primitive
// Entrées : La primitive à ajouter
// Sortie : Aucune
void ContactResolver::addPrimitive(Primitive* p) {
	primitives_.push_back(p);
}

// Rôle : Vide les listes et l'arbre
// Entrées : Aucune
// Sortie : Aucune
void ContactResolver::clear() {
	//Vide l'arbre
	tree_.clear();
	//Vide les paires
	paires_.clear();
	//Vide les primitives
	primitives_.clear();
}