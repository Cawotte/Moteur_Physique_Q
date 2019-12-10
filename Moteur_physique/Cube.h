#ifndef CUBE_H
#define CUBE_H

#include "Primitive.h"
#include "Wall.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Cube - hérite de Primitive
// But : Primitive représentant un cube
//		 Permet la gestion des collisions d'un cube
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Cube : public Primitive
{
private:
	//Calcule si un point se trouve dans le cube
	bool isPointWithinCube(Vector3D point, Vector3D* rotatedRepere);
	//Fait pivoter un point selon l'orientation de la primitive
	Vector3D rotatePointWithOrientation(Vector3D point);
	//Calcule si un point parmi une liste se trouve dans le cube
	bool arePointsCollidingWithPrimitive(Vector3D* points, int sizeArray);

public:
	//Constructeur : appelle le constructeur de primitive et passe le RigidBody et les Bounds associés
	Cube(RigidBody* body, Bounds b) : Primitive(body, b) {}
	//Destructeur
	~Cube();
	//Pivote le cube selon l'orientation de la primitive
	Vector3D* rotatedRepere();
	//Testent si le cube est en collision avec, respectivement, une primitive, un cube et un mur
	bool isPrimitiveCollidingWith(Primitive* prim);
	bool isPrimitiveCollidingWith(Cube* prim);
	bool isPrimitiveCollidingWith(Wall* prim);

};
#endif

