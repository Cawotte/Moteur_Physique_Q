#include "Octree.h"



Octree::Octree(int level, Bounds bounds)
{
	maxObj_ = 3;
	maxLevel_ = 5;
	level_ = level;
	bounds_ = bounds_;
}


Octree::~Octree()
{
}

void Octree::clear()
{
	primitives_.clear();
	vector<Octree*>::iterator it;
	for (it = nodes_.begin(); it != nodes_.end(); it++)
	{
		(*it)->clear();
	}
	nodes_.clear();
}

void Octree::split()
{
	double subWidht = bounds_.width_ / 2;
	double subHeight = bounds_.height_ / 2;
	double subDeepth = bounds_.depth_ / 2;
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_, bounds_.xmin_ + subWidht, bounds_.ymin_, bounds_.ymin_ + subHeight, bounds_.zmin_, bounds_.zmin_ + subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_ + subWidht, bounds_.xmin_ + 2*subWidht, bounds_.ymin_, bounds_.ymin_ + subHeight, bounds_.zmin_, bounds_.zmin_ + subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_ + subWidht, bounds_.xmin_ + 2 * subWidht, bounds_.ymin_ + subHeight, bounds_.ymin_ + 2 * subHeight, bounds_.zmin_, bounds_.zmin_ + subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_, bounds_.xmin_ + subWidht, bounds_.ymin_ + subHeight, bounds_.ymin_ + 2*subHeight, bounds_.zmin_, bounds_.zmin_ + subDeepth)));

	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_, bounds_.xmin_ + subWidht, bounds_.ymin_, bounds_.ymin_ + subHeight, bounds_.zmin_ + subDeepth, bounds_.zmin_ + 2*subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_ + subWidht, bounds_.xmin_ + 2 * subWidht, bounds_.ymin_, bounds_.ymin_ + subHeight, bounds_.zmin_ + subDeepth, bounds_.zmin_ + 2*subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_ + subWidht, bounds_.xmin_ + 2 * subWidht, bounds_.ymin_ + subHeight, bounds_.ymin_ + 2 * subHeight+ subDeepth, bounds_.zmin_ + subDeepth, bounds_.zmin_ + 2*subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_, bounds_.xmin_ + subWidht, bounds_.ymin_ + subHeight, bounds_.ymin_ + 2 * subHeight, bounds_.zmin_ + subDeepth, bounds_.zmin_ + 2*subDeepth)));
	
}

vector<int> Octree::getIndex(Primitive* prim)
{
	vector<int> index;
	double widthMidPoint = bounds_.xmin_ + bounds_.width_ / 2;
	double heightMidPoint = bounds_.ymin_ + bounds_.height_ / 2;
	double deepthMidPoint = bounds_.zmin_ + bounds_.depth_ / 2;
	bool topQuadrant = (prim->bounds_.ymax_ > heightMidPoint && prim->bounds_.ymin_ < bounds_.ymax_);
	bool bottomQuadrant = (prim->bounds_.ymax_ > bounds_.ymin_ && prim->bounds_.ymin_ < heightMidPoint);
	bool backQuadrant = (prim->bounds_.zmax_ > deepthMidPoint && prim->bounds_.zmin_ < bounds_.zmax_);
	bool  frontQuadrant = (prim->bounds_.zmax_ > bounds_.zmin_ && prim->bounds_.zmin_ < deepthMidPoint);
	bool leftQuadrant = (prim->bounds_.xmax_ > widthMidPoint && prim->bounds_.xmin_ < bounds_.xmax_);
	bool rightQuadrant = (prim->bounds_.xmax_ > bounds_.xmin_ && prim->bounds_.xmin_ < widthMidPoint);
	if (topQuadrant)
	{
		if (frontQuadrant)
		{
			if (leftQuadrant)
			{
				index.push_back(2);
			}
			if (rightQuadrant)
			{
				index.push_back(3);
			}
		}
		if (backQuadrant)
		{
			if (leftQuadrant)
			{
				index.push_back(6);
			}
			if (rightQuadrant)
			{
				index.push_back(7);
			}
		}
	}
	if (bottomQuadrant)
	{
		if (frontQuadrant)
		{
			if (leftQuadrant)
			{
				index.push_back(1);
			}
			if (rightQuadrant)
			{
				index.push_back(0);
			}
		}
		if (backQuadrant)
		{
			if (leftQuadrant)
			{
				index.push_back(5);
			}
			if (rightQuadrant)
			{
				index.push_back(4);
			}
		}
	}
	return index;
}

void Octree::insert(Primitive* prim)
{
	if (nodes_.size() > 0)
	{
		vector<int> indexes = getIndex(prim);
		for (int i = 0; i < indexes.size(); i++)
		{
			nodes_[indexes[i]]->insert(prim);
		}
	}
	else
	{
		primitives_.push_back(prim);
	}
	if (primitives_.size() > maxObj_ && level_<maxLevel_)
	{
		if (nodes_.size() == 0)
		{
			split();
		}
		int i = 0;
		while (i < primitives_.size())
		{
			vector<int> indexes = getIndex(primitives_[i]);
			if (indexes.size() != 0)
			{
				for (int j = 0; j < indexes.size(); j++)
				{
					nodes_[indexes[j]]->insert(primitives_[i]);
					primitives_.erase(primitives_.begin() + i);
				}
			}
			else
			{
				i++;
			}
		}
	}
}


void Octree::pairing(vector<pair<Primitive*, Primitive*>> &paires)
{
	//vector<pair<Primitive*, Primitive*>> paires;
	if (nodes_.size() != 0)
	{
		for (int j = 0; j < nodes_.size(); j++)
		{
			nodes_[j]->pairing(paires);
		}
	}

	if (primitives_.size() != 0)
	{
		for (int j = 0; j < primitives_.size(); j++)
		{
			for (int i = j+1; j < primitives_.size(); j++)
			{
				paires.push_back(pair<Primitive*, Primitive*>(primitives_[j],primitives_[i]));
			}
		}
	}
	//return paires;
}
/* Comment utiliser l'Octree :
créer un octree dans game (membre), l'itialiser avec niveau 0 et bounds englobant toute la zone où on veut faire des collisions
 à chaque boucle de jeu :
	clear l'octree clear()
	parcourir la liste des objets et les insérer dans l'octree insert(primitive)
	créer vector<pair<Primitive*, Primitive*>> paires
	appeler pairing(paires) 
	on récupère la liste des paires d'objets à tester pour les collisions
*/