#ifndef PARTICLE_FACTORY
#define PARTICLE_FACTORY


#include "IParticle.h"
#include "Particle.h"
#include "Color.h"


#include "DragFG.h"
#include "GravityFG.h"
#include "SpringFG.h"
#include "BuoyancyFG.h"
#include "AnchoredSpringFG.h"
#include "BungeeSpringFG.h"
#include "WeakSpringFG.h"
#include "ParticleGroup.h"


class ParticleFactory
{
private:

	int currentProjectileIndex_ = 0;

public:

	ParticleFactory() :	currentProjectileIndex_(0) {}

	int getCurrentProjectileIndex() { return currentProjectileIndex_; };

	std::shared_ptr<IParticle> getCurrentProjectile();

	std::shared_ptr<IParticle> nextProjectile() {
		currentProjectileIndex_++;
		currentProjectileIndex_ %= 8; //nb projectiles
		return getCurrentProjectile();
	}

	std::shared_ptr<IParticle> getBasicBall();
	std::shared_ptr<IParticle> getCannonBall();
	std::shared_ptr<IParticle> getLaser();
	std::shared_ptr<IParticle> getSnowflake();

	std::shared_ptr<IParticle> getYoyo();

	std::shared_ptr<IParticle> getBlob1();
	std::shared_ptr<IParticle> getBlob2();
	std::shared_ptr<IParticle> getTestWater();

	std::shared_ptr<IParticle> getTestBlop();
	std::shared_ptr<IParticle> getBlob3();

};

#endif

