#include "Particle.h"

Particle::Particle(Vector3D* pos, float m) : pos_(pos), vel_(Vector3D()),
	massInv_(1/m), forceAccum_(0, 0, 0)
{
	shape_ = nullptr;
}

Particle::Particle(Vector3D* pos) : pos_(pos), vel_(Vector3D()),
massInv_(0.001f), forceAccum_(0, 0, 0)
{
	shape_ = nullptr;
}

void Particle::integrer(float t)
{
	if (massInv_ >= 0 && t > 0) {
		*pos_ = *pos_ + vel_ * t;//calcul de la nouvelle position
		vel_ = vel_ + forceAccum_ * massInv_ * t;//calcul de la nouvelle velocite
		clearAccum();
	}
	else {
		*pos_ = *pos_ + vel_ * t;
	}
}

Particle::~Particle()
{
	cout << "Particle deleted" << endl;
	delete(shape_);
}


void Particle::addTo(list<Particle*> list) {
	list.push_back(this);
}

void Particle::draw() {
	shape_->draw();
	//drawVelocity(); //debug
}

void Particle::drawVelocity() {
	GlutUtils::drawLine(*getPos(), *getPos() + getVit() * 0.2f, Color::red);
}

void Particle::addForce(const Vector3D &force) {
	forceAccum_ = forceAccum_ + force;
}

void Particle::clearAccum() {
	forceAccum_ = Vector3D(0, 0, 0);
}