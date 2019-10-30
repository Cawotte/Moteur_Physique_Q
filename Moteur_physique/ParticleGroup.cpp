#include "ParticleGroup.h"



ParticleGroup::~ParticleGroup() {

	cout << "Particle Group deleted" << endl;
	//markToDeletion();
	//delete(forcesRegister_);
}

void ParticleGroup::draw() {

	std::shared_ptr<Particle> centerParticle = *particles_.begin();
	std::vector<std::shared_ptr<Particle>>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		GlutUtils::drawLine(
			*(*it)->getPos(),
			*centerParticle->getPos(),
			Color::red);

		(*it)->draw();		
	}
}

void ParticleGroup::DrawLinks() {

	std::shared_ptr<Particle> centerParticle = *particles_.begin();
	std::vector<std::shared_ptr<Particle>>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		GlutUtils::drawLine(
			*(*it)->getPos(),
			*centerParticle->getPos(),
			Color::red);
	}
}

void ParticleGroup::updateForces(float t) {

	forcesRegister_->updateForces(t);
	//We do not clear the register because we want to re-apply
	//those forces each loop
}

void ParticleGroup::addRandomOffsets() {


	std::vector<std::shared_ptr<Particle>>::iterator it;
	for (it = particles_.begin(); it != particles_.end(); it++)
	{
		//Skip the first particle
		if (it == particles_.begin()) continue;

		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4));
		float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4));

		Vector3D offset(x, y, z);
		Vector3D newPos = *(*it)->getPos() + offset;
		(*it)->setPos(newPos);
	}
}

