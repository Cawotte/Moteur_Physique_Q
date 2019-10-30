
#ifndef IPARTICLE
#define IPARTICLE

#include <list>
#include "Vector3D.h"

class IParticle {

public:
	virtual void setPos(Vector3D pos) = 0;
	virtual void setVit(Vector3D vit) = 0;

	virtual std::shared_ptr<Vector3D> getPos() = 0;
	virtual Vector3D getVit() = 0;

	virtual void draw() = 0;

};

class Particle;
class ParticleGroup;

#endif
