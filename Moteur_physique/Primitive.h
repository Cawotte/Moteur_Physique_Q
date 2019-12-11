#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "RigidBody.h"
#include "Matrix4.h"
#include "Bounds.h"

class Cube;
class Wall;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Primitive
// But : Représente une partie simplifiée d'un RigidBody
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Primitive {

protected :
	//RigidBody associé
	RigidBody* body_ = NULL;

	//Constructeur associant un RigidBody et des extrémités
	Primitive(RigidBody* body, Bounds b);
	//Constructeur par défaut
	Primitive() {};
	//Pivote un point selon une orientation
	Vector3D pointRotationByQuaternion(Vector3D point, Quaternion q);

public:
	//Extrémités actuelles
	Bounds bounds_;
	//Extrémités de la primitive sans aucune transformation appliquée
	Bounds originalBounds_;
	//Destructeur
	~Primitive();
	//Méthodes virtuelles pour tester si le cube est en collision avec, respectivement, une primitive, un cube et un mur
	virtual bool isPrimitiveCollidingWith(Primitive* prim) = 0;
	virtual bool isPrimitiveCollidingWith(Cube* prim) = 0;
	virtual bool isPrimitiveCollidingWith(Wall* prim) = 0;
	//Setter des bounds_
	void setBounds(Bounds b) { bounds_ = b; }
	//Setter des originalBounds_
	void setOriginalBounds(Bounds b) { originalBounds_ = b; }
	//Mise à jour des bounds_
	void updateBounds();
	//Getter du RigidBody
	RigidBody* getBody() { return body_; }

};

#endif
