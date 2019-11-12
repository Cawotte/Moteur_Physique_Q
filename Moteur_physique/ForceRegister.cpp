#include "ForceRegister.h"

ForceRegister::ForceRegister()
{
}


ForceRegister::~ForceRegister()
{
	clear();
}

void ForceRegister::add(RigidBody* rb, ForceGenerator* fg) {
	ForceRecord fr;
	fr.fg = fg;
	fr.rb = rb;
	register_.push_back(fr);
}


void ForceRegister::add(std::vector<ForceRecord> otherRegister) {
		
	std::vector<ForceRecord>::iterator it;
	for (it = otherRegister.begin(); it != otherRegister.end(); it++)
	{
		this->add(it->rb, it->fg);
	}
}

void ForceRegister::remove() {
	register_.pop_back();
}

void ForceRegister::clear() {
	std::vector<ForceRecord>::iterator it;
	register_.clear();
}

void ForceRegister::updateForces(float t) {
	std::vector<ForceRecord>::iterator it;
	for (it = register_.begin(); it != register_.end(); it++)
	{
		if (it->rb != NULL) {
			it->fg->updateForce(it->rb, t);
		}
	}
}