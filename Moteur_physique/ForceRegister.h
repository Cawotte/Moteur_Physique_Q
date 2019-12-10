#ifndef PARTICLEFORCEREGISTER_H
#define PARTICLEFORCEREGISTER_H

#include <vector>
#include "ForceGenerator.h"
#include "RigidBody.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : ForceRecord
// But : Associe un pointeur de RigidBody et un pointeur de générateur de force
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
	//Ajoute un nouveau ForceRecords à register_ à partir d'un RigidBody et d'un ForceGenerator
	void add(RigidBody* rb, ForceGenerator* fg);
	//Ajoute un nouveau ForceRecords à register_ 
	void add(std::vector<ForceRecord> otherRegister);
	//Enlève le dernier élément de register_
	void remove();
	//Vide register_
	void clear();
	//Appelle updateForce pour chaque ForceGenerator des ForceRecords de register_ en fonction du temps
	void updateForces(float t);
	//Retourne register_
	std::vector<ForceRecord> getRegister() {
		return register_;
	}
	//Constructeur par défaut
	ForceRegister();
	//Destructeur
	~ForceRegister();
};

#endif