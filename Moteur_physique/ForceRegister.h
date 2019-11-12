#ifndef PARTICLEFORCEREGISTER_H
#define PARTICLEFORCEREGISTER_H

#include <vector>
#include "ForceGenerator.h"
#include "RigidBody.h"

struct ForceRecord {
	RigidBody* rb;
	ForceGenerator* fg;
};

class ForceRegister {

private:

	std::vector<ForceRecord> register_;

public:

	void add(RigidBody* rb, ForceGenerator* fg);
	void add(std::vector<ForceRecord> otherRegister);
	void remove();
	void clear();
	void updateForces(float t);

	std::vector<ForceRecord> getRegister() {
		return register_;
	}

	ForceRegister();
	~ForceRegister();
};

#endif