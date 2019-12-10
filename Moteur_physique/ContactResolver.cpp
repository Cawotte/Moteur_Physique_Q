#include "ContactResolver.h"


// R�le : Constructeur par d�faut - Initialise l'objet 
// Entr�es : Aucune
// Sortie : Aucune
ContactResolver::ContactResolver()
{
}

// R�le : Vide et d�truit l'objet 
// Entr�es : Aucune
// Sortie : Aucune
ContactResolver::~ContactResolver()
{
	clear();
}

// R�le : Effectue la broad phase
// Entr�es : Aucune
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

// R�le : Affiche le r�sultat de la broad phase 
// Entr�es : Aucune
// Sortie : Aucune
void ContactResolver::displayBroadPhase() {
	//Affiche l'octree
	tree_.display();
	//Affiche chaque paire calcul�e
	for (int k = 0; k < paires_.size(); k++)
	{
		cout << "paire numero " << k;
		cout << " (" << (paires_[k].first->bounds_.xmin_ + paires_[k].first->bounds_.xmax_) / 2 << " " << (paires_[k].first->bounds_.ymin_ + paires_[k].first->bounds_.ymax_) / 2 << " " << (paires_[k].first->bounds_.zmin_ + paires_[k].first->bounds_.zmax_) / 2 << ") ";
		cout << "(" << (paires_[k].second->bounds_.xmin_ + paires_[k].second->bounds_.xmax_) / 2 << " " << (paires_[k].second->bounds_.ymin_ + paires_[k].second->bounds_.ymax_) / 2 << " " << (paires_[k].second->bounds_.zmin_ + paires_[k].second->bounds_.zmax_) / 2 << ")" << endl;
	}
}

// R�le : Effectue la narrow phase 
// Entr�es : Aucune
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

// R�le : Teste si les deux primitives sont en collision
// Entr�es : Aucune
// Sortie : S'il y a collision
bool ContactResolver::hasCollision(Primitive* a, Primitive* b) {	

	return (a->isPrimitiveCollidingWith(b) || b->isPrimitiveCollidingWith(a));

}

// R�le : Ajoute une primitive
// Entr�es : La primitive � ajouter
// Sortie : Aucune
void ContactResolver::addPrimitive(Primitive* p) {
	primitives_.push_back(p);
}

// R�le : Vide les listes et l'arbre
// Entr�es : Aucune
// Sortie : Aucune
void ContactResolver::clear() {
	//Vide l'arbre
	tree_.clear();
	//Vide les paires
	paires_.clear();
	//Vide les primitives
	primitives_.clear();
}