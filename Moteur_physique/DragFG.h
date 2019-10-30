#ifndef DRAG_FORCE_GENERATOR
#define DRAG_FORCE_GENERATOR

#include "ParticleForceGenerator.h"
class DragFG : public ParticleForceGenerator
{
private:

	float k1_;
	float k2_;

public:
	DragFG(float k1, float k2) : k1_(k1), k2_(k2) {

	}

	void updateForce(Particle* p, float t);

	//get
	float getK1() { return k1_; }
	float getK2() { return k2_; }

	//set
	void setK1(float k1) { k1_ = k1; }
	void setK2(float k2) { k2_ = k2; }
};

#endif

