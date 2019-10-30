
#ifndef PHYSIC_SIMULATOR
#define PHYSIC_SIMULATOR

#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

#include "ParticleForceRegister.h"
#include "ContactResolver.h"
#include "ParticleGroup.h"
#include "Contact.h"

#include "DragFG.h"
#include "GravityFG.h"
#include "SpringFG.h"
#include "BuoyancyFG.h"
#include "AnchoredSpringFG.h"
#include "BungeeSpringFG.h"
#include "WeakSpringFG.h"

class PhysicSimulator
{

private:


	//Registre des forces
	ParticleForceRegister register_;

	//Collisions
	ContactResolver contactResolver_;

	//Particules à simuler
	list <std::shared_ptr<Particle>> particles_; //liste des particules créées
	list <std::shared_ptr<ParticleGroup>> particlesGroups_;

	//Constantes
	Vector3D g_ = Vector3D(0, 0, -9.8f);
	float k1 = 0.5f;
	float k2 = 1.2f;


	//Updates de la simulation

	int resolveCollisions();

	ParticleContact* getContact(Particle* pa, Particle* pb);

	void applyRegister(float elapsedTime);
	void applyCollisions(float elapsedTime);
	void applyMovements(float elapsedTime);
	void verifyDeletion();

	bool isInPool(Particle* p);

	void drawParticles();
	void drawGroupParticles();

public:


	PhysicSimulator() 
	{
	};

	~PhysicSimulator() {
		deleteAllParticles();
	}

	void addParticle(std::shared_ptr<IParticle> pa);
	void deleteParticle(std::shared_ptr<Particle> pa);
	void deleteParticleGroup(std::shared_ptr<ParticleGroup> paG);
	void deleteAllParticles();
	void deleteAndClearAll();

	void updatePhysics(float elapsedTime);

	void draw();

	list <std::shared_ptr<Particle>> getParticles() {
		return particles_;
	}

	list <std::shared_ptr<ParticleGroup>> getParticuleGroups() {
		return particlesGroups_;
	}

};


#endif