#include "ContactResolver.h"



ContactResolver::ContactResolver()
{
}


ContactResolver::~ContactResolver()
{
	clear();
}

void ContactResolver::broadPhase() {
	//vide l'octree
	tree_.clear();
	//ajoute chaque primitive dans l'octree
	std::list<Primitive*>::iterator it;
	for (it = primitives_.begin(); it != primitives_.end(); it++)
	{
		tree_.insert((*it));
	}
	//vide la liste de paires
	paires_.clear();
	//effectue le pairing
	tree_.pairing(paires_);
}

void ContactResolver::displayBroadPhase() {
	tree_.display();

	//affiche chaque paire calculée
	for (int k = 0; k < paires_.size(); k++)
	{
		cout << "paire numero " << k;
		cout << " (" << (paires_[k].first->bounds_.xmin_ + paires_[k].first->bounds_.xmax_) / 2 << " " << (paires_[k].first->bounds_.ymin_ + paires_[k].first->bounds_.ymax_) / 2 << " " << (paires_[k].first->bounds_.zmin_ + paires_[k].first->bounds_.zmax_) / 2 << ") ";
		cout << "(" << (paires_[k].second->bounds_.xmin_ + paires_[k].second->bounds_.xmax_) / 2 << " " << (paires_[k].second->bounds_.ymin_ + paires_[k].second->bounds_.ymax_) / 2 << " " << (paires_[k].second->bounds_.zmin_ + paires_[k].second->bounds_.zmax_) / 2 << ")" << endl;
	}
}

int ContactResolver::narrowPhase() {
	int collisions = 0;
	std::vector<pair<Primitive*, Primitive*>>::iterator itp;
	for (itp = paires_.begin(); itp != paires_.end(); itp++)
	{
		Primitive* a = itp->first;
		Primitive* b = itp->second;
		if (hasCollision(a, b)) {
			cout << "Collision!" << endl;
			collisions += 1;
			//ajouter les données du contact a une liste de contacts
		}
	}
	return collisions;
}

bool ContactResolver::hasCollision(Primitive* a, Primitive* b) {	

	return (a->isPrimitiveCollidingWith(b) || b->isPrimitiveCollidingWith(a));
	/*
	Wall* aW = dynamic_cast<Wall*>(a);
	Wall* bW = dynamic_cast<Wall*>(b);
	if (aW == NULL) {
		if (bW == NULL) {
			//Collision entre deux box
			Vector3D* aRep = a->rotatedRepere();
			Vector3D* bRep = b->rotatedRepere();
			for (int i = 0; i < 8; i++) {
				if (a->pointIsWithinBox(bRep[i], aRep)) {
					return true;
				}
			}

			return false;
		}
		else {
			//Collision de a avec le mur bW
			return false;
		}
	}
	else if (bW == NULL) {
		//Collision de b avec le mur aW
		return false;
	}
	*/
}

void ContactResolver::addPrimitive(Primitive* p) {
	primitives_.push_back(p);
}

void ContactResolver::clear() {
	tree_.clear();
	paires_.clear();
	primitives_.clear();
}