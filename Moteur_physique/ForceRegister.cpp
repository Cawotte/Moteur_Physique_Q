#include "ForceRegister.h"

// Rôle : Constructeur par défaut - Initialise l'objet 
// Entrées : Aucune
// Sortie : Aucune
ForceRegister::ForceRegister()
{
}

// Rôle : Destructeur - Détruit l'objet en vidant register_
// Entrées : Aucune
// Sortie : Aucune
ForceRegister::~ForceRegister()
{
	clear();
}

// Rôle : Ajoute un nouveau ForceRecords à register_ à partir d'un RigidBody et d'un ForceGenerator
// Entrées : Un pointeur sur un RigidBody et un pointeur sur un ForceGenerator à associer dans un ForceRecord et à ajouter dans register_
// Sortie : Aucune
void ForceRegister::add(RigidBody* rb, ForceGenerator* fg) {
	//création d'un ForceRecord
	ForceRecord fr;
	//Initialisation de ses membres
	fr.fg = fg;
	fr.rb = rb;
	//Ajout du ForceRecord à register_
	register_.push_back(fr);
}

// Rôle : Ajoute un nouveau ForceRecords à register_ 
// Entrées : Un autre registre (vecteur de ForceRecord) à ajouter dans register_
// Sortie : Aucune
void ForceRegister::add(std::vector<ForceRecord> otherRegister) {
	//Pour chaque ForceRecord dans otherRegister on l'ajoute dans register_	
	std::vector<ForceRecord>::iterator it;
	for (it = otherRegister.begin(); it != otherRegister.end(); it++)
	{
		this->add(it->rb, it->fg);
	}
}

// Rôle : Enlève le dernier élément de register_
// Entrées : Aucune
// Sortie : Aucune
void ForceRegister::remove() {
	register_.pop_back();
}

// Rôle : Vide Register
// Entrées : Aucune
// Sortie : Aucune
void ForceRegister::clear() {
	//Pour chaque ForceRecord, libère le pointeur de ForceGenerator associé
	std::vector<ForceRecord>::iterator it;
	for (it = register_.begin(); it != register_.end(); it++)
	{
		delete(it->fg);
	}
	//Vide le vecteur
	register_.clear();
}

// Rôle : Appelle updateForce pour chaque ForceGenerator des ForceRecords de register_ en fonction du temps
// Entrées : temps t
// Sortie : Aucune
void ForceRegister::updateForces(float t) {
	//Pour chaque ForceRecord dans register_
	std::vector<ForceRecord>::iterator it;
	for (it = register_.begin(); it != register_.end(); it++)
	{
		if (it->rb != NULL) //Si le RigidBody du ForceRecord n'est pas null
		{
			//On appelle updateForce du ForceGenerator en lui passant en paramètre le RigidBody qui lui est associé et le temps t
			it->fg->updateForce(it->rb, t);
		}
	}
}