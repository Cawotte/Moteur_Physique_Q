#ifndef OCTREE_H
#define OCTREE_H
#include"Primitive.h"
#include <vector>
#include "Bounds.h"

class Octree
{
private:
	int maxObj_;
	int maxLevel_;
	int level_;
	vector<Primitive*> primitives_;
	vector<Octree*> nodes_;
	int nbObj_;
	Bounds bounds_;

public:
	Octree(int level, Bounds bounds);
	~Octree();
	void clear();
	void split();
	vector<int> getIndex(Primitive* prim);
	//bool inArea(Primitive* prim);
	void insert(Primitive* prim);
	void pairing(vector<pair<Primitive*, Primitive*>> &paires);
};
#endif