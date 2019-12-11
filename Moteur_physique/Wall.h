#ifndef WALL_H
#define WALL_H

#include "Primitive.h"
#include "Cube.h"
#include "ContactResolver.h"

//Les différents types de murs
enum typeWall {
	frontWall,
	rightWall,
	leftWall,
	upWall,
	downWall,
	behindWall
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Wall - hérite de primitive
// But : Primitive représentant un mur
//		 Permet la gestion des collisions d'un mur
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Wall : public Primitive {

private:
	//type du mur
	typeWall type_;
	//vecteur normal au mur
	Vector3D normal_;
	//décalage du mur
	float offset_ = 0.f;

public:
	//Constructeur initialisant le type du mur
	Wall(typeWall type);
	//Destructeur
	~Wall();
	//Testent si le cube est en collision avec, respectivement, une primitive, un cube et un mur
	bool isPrimitiveCollidingWith(Primitive* prim);
	bool isPrimitiveCollidingWith(Cube* prim);
	bool isPrimitiveCollidingWith(Wall* prim);
	//Getter du type du mur
	typeWall getType() { return type_; }
	//Getter de la normale
	Vector3D getNormal() { return normal_; }
};

#endif