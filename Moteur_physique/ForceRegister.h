#ifndef PARTICLEFORCEREGISTER_H
#define PARTICLEFORCEREGISTER_H

#include <vector>
#include "ForceGenerator.h"
#include "RigidBody.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : ForceRecord
// But : Associe un pointeur de RigidBody et un pointeur de g�n�rateur de force
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ForceRecord {
	RigidBody* rb;
	ForceGenerator* fg;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : ForceRegister
// But : Stocke les ForceRecords : paires RigidBody/ForceGenerator
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ForceRegister {

private:
	//vecteur des ForceRecords qu'il contient
	std::vector<ForceRecord> register_;

public:
	//Ajoute un nouveau ForceRecords � register_ � partir d'un RigidBody et d'un ForceGenerator
	void add(RigidBody* rb, ForceGenerator* fg);
	//Ajoute un nouveau ForceRecords � register_ 
	void add(std::vector<ForceRecord> otherRegister);
	//Enl�ve le dernier �l�ment de register_
	void remove();
	//Vide register_
	void clear();
	//Appelle updateForce pour chaque ForceGenerator des ForceRecords de register_ en fonction du temps
	void updateForces(float t);
	//Retourne register_
	std::vector<ForceRecord> getRegister() {
		return register_;
	}
	//Constructeur par d�faut
	ForceRegister();
	//Destructeur
	~ForceRegister();
};

#endif