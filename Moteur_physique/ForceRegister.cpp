#include "ForceRegister.h"

// R�le : Constructeur par d�faut - Initialise l'objet 
// Entr�es : Aucune
// Sortie : Aucune
ForceRegister::ForceRegister()
{
}

// R�le : Destructeur - D�truit l'objet en vidant register_
// Entr�es : Aucune
// Sortie : Aucune
ForceRegister::~ForceRegister()
{
	clear();
}

// R�le : Ajoute un nouveau ForceRecords � register_ � partir d'un RigidBody et d'un ForceGenerator
// Entr�es : Un pointeur sur un RigidBody et un pointeur sur un ForceGenerator � associer dans un ForceRecord et � ajouter dans register_
// Sortie : Aucune
void ForceRegister::add(RigidBody* rb, ForceGenerator* fg) {
	//cr�ation d'un ForceRecord
	ForceRecord fr;
	//Initialisation de ses membres
	fr.fg = fg;
	fr.rb = rb;
	//Ajout du ForceRecord � register_
	register_.push_back(fr);
}

// R�le : Ajoute un nouveau ForceRecords � register_ 
// Entr�es : Un autre registre (vecteur de ForceRecord) � ajouter dans register_
// Sortie : Aucune
void ForceRegister::add(std::vector<ForceRecord> otherRegister) {
	//Pour chaque ForceRecord dans otherRegister on l'ajoute dans register_	
	std::vector<ForceRecord>::iterator it;
	for (it = otherRegister.begin(); it != otherRegister.end(); it++)
	{
		this->add(it->rb, it->fg);
	}
}

// R�le : Enl�ve le dernier �l�ment de register_
// Entr�es : Aucune
// Sortie : Aucune
void ForceRegister::remove() {
	register_.pop_back();
}

// R�le : Vide Register
// Entr�es : Aucune
// Sortie : Aucune
void ForceRegister::clear() {
	//Pour chaque ForceRecord, lib�re le pointeur de ForceGenerator associ�
	std::vector<ForceRecord>::iterator it;
	for (it = register_.begin(); it != register_.end(); it++)
	{
		delete(it->fg);
	}
	//Vide le vecteur
	register_.clear();
}

// R�le : Appelle updateForce pour chaque ForceGenerator des ForceRecords de register_ en fonction du temps
// Entr�es : temps t
// Sortie : Aucune
void ForceRegister::updateForces(float t) {
	//Pour chaque ForceRecord dans register_
	std::vector<ForceRecord>::iterator it;
	for (it = register_.begin(); it != register_.end(); it++)
	{
		if (it->rb != NULL) //Si le RigidBody du ForceRecord n'est pas null
		{
			//On appelle updateForce du ForceGenerator en lui passant en param�tre le RigidBody qui lui est associ� et le temps t
			it->fg->updateForce(it->rb, t);
		}
	}
}