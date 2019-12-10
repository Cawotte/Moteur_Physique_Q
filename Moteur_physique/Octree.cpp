#include "Octree.h"

// Rôle : Constructeur - Initialise l'objet
// Entrées : Le niveau actuel de l'octree et les extrémités du niveau
// Sortie : Aucune
Octree::Octree(int level, Bounds b)
{
	maxObj_ = 3;
	maxLevel_ = 5;
	level_ = level;
	bounds_ = b;	
}

// Rôle : Détruit l'objet
// Entrées : Aucune
// Sortie : Aucune
Octree::~Octree()
{
}

// Rôle : Vide l'octree
// Entrées : Aucune
// Sortie : Aucune
void Octree::clear()
{
	//Vide les primitives du niveau
	primitives_.clear();
	vector<Octree*>::iterator it;
	//Appel récursif de cette méthode pour chaque subdivision
	for (it = nodes_.begin(); it != nodes_.end(); it++)
	{
		(*it)->clear();
	}
	//Vide les subdivisions
	nodes_.clear();
}

// Rôle : Subdivise le niveau courant de l'octree
// Entrées : Aucune
// Sortie : Aucune
void Octree::split()
{
	//Calcule les demi-dimensions
	float subWidht = bounds_.width_ / 2;
	float subHeight = bounds_.height_ / 2;
	float subDeepth = bounds_.depth_ / 2;
	//Création et ajout de chaque subdivision : un nouvel octree à chaque fois, pour découper le niveau actuel en 8 parts égales
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_, bounds_.xmin_ + subWidht, bounds_.ymin_, bounds_.ymin_ + subHeight, bounds_.zmin_, bounds_.zmin_ + subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_ + subWidht, bounds_.xmin_ + 2 * subWidht, bounds_.ymin_, bounds_.ymin_ + subHeight, bounds_.zmin_, bounds_.zmin_ + subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_ + subWidht, bounds_.xmin_ + 2 * subWidht, bounds_.ymin_ + subHeight, bounds_.ymin_ + 2 * subHeight, bounds_.zmin_, bounds_.zmin_ + subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_, bounds_.xmin_ + subWidht, bounds_.ymin_ + subHeight, bounds_.ymin_ + 2 * subHeight, bounds_.zmin_, bounds_.zmin_ + subDeepth)));

	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_, bounds_.xmin_ + subWidht, bounds_.ymin_, bounds_.ymin_ + subHeight, bounds_.zmin_ + subDeepth, bounds_.zmin_ + 2 * subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_ + subWidht, bounds_.xmin_ + 2 * subWidht, bounds_.ymin_, bounds_.ymin_ + subHeight, bounds_.zmin_ + subDeepth, bounds_.zmin_ + 2 * subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_ + subWidht, bounds_.xmin_ + 2 * subWidht, bounds_.ymin_ + subHeight, bounds_.ymin_ + 2 * subHeight + subDeepth, bounds_.zmin_ + subDeepth, bounds_.zmin_ + 2 * subDeepth)));
	nodes_.push_back(new Octree(level_ + 1, Bounds(bounds_.xmin_, bounds_.xmin_ + subWidht, bounds_.ymin_ + subHeight, bounds_.ymin_ + 2 * subHeight, bounds_.zmin_ + subDeepth, bounds_.zmin_ + 2 * subDeepth)));

}

// Rôle : /Calcule les subdivisions auxquelles appartient la primitive en paramètre
// Entrées : La primitive dont on veut l'index
// Sortie : La liste des indices de subdivisions auxquelles appartient la primitive
vector<int> Octree::getIndex(Primitive* prim)
{
	//Liste des indexs
	vector<int> index;
	//Points médians des dimensions du niveau actuel
	float widthMidPoint = bounds_.xmin_ + bounds_.width_ / 2;
	float heightMidPoint = bounds_.ymin_ + bounds_.height_ / 2;
	float deepthMidPoint = bounds_.zmin_ + bounds_.depth_ / 2;
	//Si la primitive est à cheval respectivement sur les parties hautes, basses, arrière, avant, gauche et droite du niveau
	bool topQuadrant = (prim->bounds_.ymax_ > heightMidPoint && prim->bounds_.ymin_ < bounds_.ymax_);
	bool bottomQuadrant = (prim->bounds_.ymax_ > bounds_.ymin_ && prim->bounds_.ymin_ < heightMidPoint);
	bool backQuadrant = (prim->bounds_.zmax_ > deepthMidPoint && prim->bounds_.zmin_ < bounds_.zmax_);
	bool frontQuadrant = (prim->bounds_.zmax_ > bounds_.zmin_ && prim->bounds_.zmin_ < deepthMidPoint);
	bool leftQuadrant = (prim->bounds_.xmax_ > widthMidPoint && prim->bounds_.xmin_ < bounds_.xmax_);
	bool rightQuadrant = (prim->bounds_.xmax_ > bounds_.xmin_ && prim->bounds_.xmin_ < widthMidPoint);

	//Ajout à la liste des indices appropriés selon les valeurs des booléens calculés précédemment
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

// Rôle : Insert la primirive dans l'octree
// Entrées : La primitive à ajouter
// Sortie : Aucune
void Octree::insert(Primitive* prim)
{
	//S'il existe des subdivisions au niveau actuel
	if (nodes_.size() > 0)
	{
		//Calcul des subdivisions que la primitive chevauche
		vector<int> indexes = getIndex(prim);
		for (int i = 0; i < indexes.size(); i++)
		{
			//Appel récursif sur les subdivisions concernées
			nodes_[indexes[i]]->insert(prim);
		}
	}
	else
	{
		//Sinon on ajoute la primitive au niveau actuel
		primitives_.push_back(prim);
	}
	//Si on dépasse le maximum d'objets par niveau et que l'on n'a pas atteint le maximum de niveaux
	if (primitives_.size() > maxObj_ && level_<maxLevel_)
	{
		//S'il n'y a pas encore de subdivisions, on subdivise
		if (nodes_.size() == 0)
		{
			split();
		}
		int i = 0;
		//Tant que l'on a pas déplace chaque primitive du niveau actuel
		while (i < primitives_.size())
		{
			//On récupère les subdivisions que la primitive chevauche
			vector<int> indexes = getIndex(primitives_[i]);	
			//Si la primitive n'est pas nulle part
			if (indexes.size() != 0)
			{
				//Pour chaque subdivision concernée
				for (int j = 0; j < indexes.size(); j++)
				{
					nodes_[indexes[j]]->insert(primitives_[i]);

					//SI CAPLANTE CA PEUT VENIR DE LA
				}
				primitives_.erase(primitives_.begin() + i);
			}
			else
			{
				//sinon on passe à la subdivision suivante
				i++;
			}
		}
	}
}

// Rôle : Détruit l'objet
// Entrées : Aucune
// Sortie : Aucune
void Octree::pairing(vector<pair<Primitive*, Primitive*>> &paires)
{
	if (nodes_.size() != 0)
	{
		for (int j = 0; j < nodes_.size(); j++)
		{
			nodes_[j]->pairing(paires);
		}
	}

	if (primitives_.size() >1)
	{
		for (int j = 0; j < primitives_.size()-1; j++)
		{
			for (int i = j+1; i < primitives_.size(); i++)
			{
				paires.push_back(pair<Primitive*, Primitive*>(primitives_[j],primitives_[i]));
			}
		}
	}
}

// Rôle : Détruit l'objet
// Entrées : Aucune
// Sortie : Aucune
void Octree::display()
{
	for (int u = 0; u < level_; u++)
	{
		cout << '\t';
	}
	cout << level_ << " ";
	if (nodes_.size() != 0)
	{
		cout << endl;
		for (int j = 0; j < nodes_.size(); j++)
		{
			nodes_[j]->display();
		}
	}
	if (primitives_.size() != 0)
	{
		for (int j = 0; j < primitives_.size(); j++)
		{			
			cout << "  ("<< j+1<<")"<<(primitives_[j]->bounds_.xmin_ + primitives_[j]->bounds_.xmax_) / 2 << " " << (primitives_[j]->bounds_.ymin_ + primitives_[j]->bounds_.ymax_) / 2 << " " << (primitives_[j]->bounds_.zmin_ + primitives_[j]->bounds_.zmax_) / 2 << " ";
		}		
	}
	cout << endl;
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