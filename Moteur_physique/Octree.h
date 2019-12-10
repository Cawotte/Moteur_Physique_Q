#ifndef OCTREE_H
#define OCTREE_H
#include"Primitive.h"
#include <vector>
#include "Bounds.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Octree
// But : Permet d'effectuer la broad phase lors de la détection de collision
//		 Récursif, représente en réalité un seul niveau de l'octree
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Octree
{
private:
	//Maximum d'objets dans un niveau de l'octree
	int maxObj_;
	//Maximum de niveau de l'octree
	int maxLevel_;
	//Niveau actuel de subdivision de l'octree
	int level_;
	//Liste des primitives dans ce niveau de l'octree
	vector<Primitive*> primitives_;
	//Liste des subdivisions de ce niveau de l'octree
	vector<Octree*> nodes_;
	//Nombre d'objets dans ce niveau de l'octree
	int nbObj_;
	//Extrémités de ce niveau de l'octree, nulles par défaut
	Bounds bounds_ = Bounds(0, 0, 0, 0, 0, 0);;

public:
	//Constructeur
	Octree(int level, Bounds b);
	//Destructeur
	~Octree();
	//Vide l'octree
	void clear();
	//Subdivise le niveau courant de l'octree
	void split();
	//Calcule les subdivisions auxquelles appartient la primitive en paramètre
	vector<int> getIndex(Primitive* prim);
	//Insert la primirive dans l'octree
	void insert(Primitive* prim);
	//Calcule les paires de primitives pour lesquelles il est pertinent d'appliquer la nnarrow phase
	void pairing(vector<pair<Primitive*, Primitive*>> &paires);
	//Affiche l'arbre
	void display();
};
#endif
