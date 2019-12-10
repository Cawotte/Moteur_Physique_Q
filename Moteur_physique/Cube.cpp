#include "Cube.h"

// Rôle : Détruit l'objet
// Entrées : Aucune
// Sortie : Aucune
Cube::~Cube()
{
}

// Rôle : Pivote le cube selon l'orientation de la primitive
// Entrées : Aucune
// Sortie : 9 Vector3D représentant les extrémités + le centre du cube une fois rotaté 
Vector3D* Cube::rotatedRepere()
{
	Vector3D* points = new Vector3D[9];

	//Points du repère
	points[0] = Vector3D{ bounds_.xmin_, bounds_.ymin_, bounds_.zmin_ }; //p1
	points[1] = Vector3D{ bounds_.xmax_, bounds_.ymin_, bounds_.zmin_ }; //p2
	points[3] = Vector3D{ bounds_.xmin_, bounds_.ymax_, bounds_.zmin_ }; //p4
	points[4] = Vector3D{ bounds_.xmin_, bounds_.ymin_, bounds_.zmax_ }; //p5

	points[2] = Vector3D{ bounds_.xmax_, bounds_.ymax_, bounds_.zmin_ }; //p3
	points[6] = Vector3D{ bounds_.xmax_, bounds_.ymax_, bounds_.zmax_ }; //p7
	points[7] = Vector3D{ bounds_.xmin_, bounds_.ymax_, bounds_.zmax_ }; //p8
	points[5] = Vector3D{ bounds_.xmax_, bounds_.ymin_, bounds_.zmax_ }; //p6

	points[8] = (points[0] + points[6]) * 0.5f;


	Quaternion q = body_->getOrientation();

	//Points déplacés et rotatés autour du centre du pivot
	for (int i = 0; i < 8; i++) {
		points[i] = points[i] + body_->getPosition();
		points[i] = pointRotationByQuaternion(points[i], q);
	}
	return points;
}

// Rôle : Calcule si un point se trouve dans le cube
// Entrées : Le point à tester et le cube rotaté
// Sortie : Booléen : si le point est dans le cube
bool Cube::isPointWithinCube(Vector3D point, Vector3D* p)
{
	float xLenght = (p[1] - p[0]).norm();
	float yLenght = (p[3] - p[0]).norm();
	float zLenght = (p[4] - p[0]).norm();

	Vector3D xLocal = (p[1] - p[0]) * (1.f / xLenght);
	Vector3D yLocal = (p[3] - p[0]) * (1.f / yLenght);
	Vector3D zLocal = (p[4] - p[0]) * (1.f / zLenght);

	Vector3D pivot = p[8];

	Vector3D v = point - pivot;

	float px = abs(v.dotProd(xLocal));
	float py = abs(v.dotProd(yLocal));
	float pz = abs(v.dotProd(zLocal));

	return (2 * px <= xLenght &&
		2 * py <= yLenght &&
		2 * pz <= zLenght
		);
}

// Rôle : Fait pivoter un point selon l'orientation de la primitive
// Entrées : Le point à faire pivoter dans le repère du cube
// Sortie : Le point rotaté
Vector3D Cube::rotatePointWithOrientation(Vector3D point)
{
	return pointRotationByQuaternion(point, body_->getOrientation());
}

// Rôle : Teste si le cube est en collision avec une primitive
// Entrées : La primitive avec laquelle la collision est testée
// Sortie : S'il y a collision
bool Cube::isPrimitiveCollidingWith(Primitive* prim)
{
	return prim->isPrimitiveCollidingWith(this);
}

// Rôle : Teste si le cube est en collision avec un autre cube
// Entrées : Le cube avec lequel la collision est testée
// Sortie : S'il y a collision
bool Cube::isPrimitiveCollidingWith(Cube* prim)
{
	return arePointsCollidingWithPrimitive(prim->rotatedRepere(), 8);
}

// Rôle : Teste si le cube est en collision avec un mur
// Entrées : Le mur avec lequel la collision est testée
// Sortie : S'il y a collision
bool Cube::isPrimitiveCollidingWith(Wall* prim)
{
	return prim->isPrimitiveCollidingWith(this);
}

// Rôle : //Calcule si un point parmi une liste se trouve dans le cube
// Entrées : Les points à tester, et leur nombre
// Sortie : Si au moins un des points est dans le cube
bool Cube::arePointsCollidingWithPrimitive(Vector3D* points, int nbPoints)
{
	Vector3D* repere = rotatedRepere();

	for (int i = 0; i < nbPoints; i++) 
	{
		if (isPointWithinCube(points[i], repere)) 
		{
			return true;
		}
	}

	return false;
}
