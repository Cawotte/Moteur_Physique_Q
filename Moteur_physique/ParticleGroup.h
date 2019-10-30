#include "Vector3D.h"
#ifndef PARTICLE_GROUP
#define PARTICLE_GROUP

#include "IParticle.h"
#include "Particle.h"
#include "ParticleForceRegister.h"
#include "Color.h"

class ParticleGroup : public IParticle
{
private:

	std::vector<std::shared_ptr<Particle>> particles_;
	ParticleForceRegister* forcesRegister_; //Forces specific to that group
	void addRandomOffsets();

	bool markedToDeletion_ = false;

public:

	ParticleGroup(std::vector<std::shared_ptr<Particle>> particles, ParticleForceRegister* forcesRegister)
		: particles_(particles), forcesRegister_(forcesRegister)
	{
		addRandomOffsets();
	}


	~ParticleGroup();

	//Getter and Setter

	//Set central particle to new pos and keep the offset between them
	void setPos(Vector3D pos) {

		std::vector<std::shared_ptr<Particle>>::iterator it;

		Vector3D initialFirstParticlePos = *getPos();

		for (it = particles_.begin(); it != particles_.end(); it++)
		{
			Vector3D initialPos = *(*it)->getPos();
			Vector3D offset = initialFirstParticlePos - initialPos;

			(*it)->setPos(pos + offset);
		}
	};

	//Set all particles to the same speed
	void setVit(Vector3D vit) {
		std::vector<std::shared_ptr<Particle>>::iterator it;
		for (it = particles_.begin(); it != particles_.end(); it++)
		{
			(*it)->setVit(vit);
		}
	};

	bool isMarkedToDeletion() {
		return markedToDeletion_;
	}

	std::shared_ptr<Vector3D> getPos() {
		//Return the pos of the first particle
		return (*particles_.begin())->getPos();
	};


	Vector3D getVit() {
		return (*particles_.begin())->getVit();
	}

	std::vector<std::shared_ptr<Particle>> getParticles() {
		return particles_;
	}

	void markToDeletion() {
		markedToDeletion_ = true;
		std::vector<std::shared_ptr<Particle>>::iterator it;
		for (it = particles_.begin(); it != particles_.end(); it++)
		{
			(*it)->markToDeletion();
		}
	}

	void draw(); 
	void DrawLinks();

	void updateForces(float elapsedTime);


};

#endif

