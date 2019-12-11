#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "RigidBody.h"
#include "Matrix4.h"
#include "Bounds.h"

class Cube;
class Wall;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Primitive
// But : Repr�sente une partie simplifi�e d'un RigidBody
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Primitive {

protected :
	//RigidBody associ�
	RigidBody* body_ = NULL;

	//Constructeur associant un RigidBody et des extr�mit�s
	Primitive(RigidBody* body, Bounds b);
	//Constructeur par d�faut
	Primitive() {};
	//Pivote un point selon une orientation
	Vector3D pointRotationByQuaternion(Vector3D point, Quaternion q);

public:
	//Extr�mit�s actuelles
	Bounds bounds_;
	//Extr�mit�s de la primitive sans aucune transformation appliqu�e
	Bounds originalBounds_;
	//Destructeur
	~Primitive();
	//M�thodes virtuelles pour tester si le cube est en collision avec, respectivement, une primitive, un cube et un mur
	virtual bool isPrimitiveCollidingWith(Primitive* prim) = 0;
	virtual bool isPrimitiveCollidingWith(Cube* prim) = 0;
	virtual bool isPrimitiveCollidingWith(Wall* prim) = 0;
	//Setter des bounds_
	void setBounds(Bounds b) { bounds_ = b; }
	//Setter des originalBounds_
	void setOriginalBounds(Bounds b) { originalBounds_ = b; }
	//Mise � jour des bounds_
	void updateBounds();
	//Getter du RigidBody
	RigidBody* getBody() { return body_; }

};

#endif
