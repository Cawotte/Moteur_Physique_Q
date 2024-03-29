#include "Wall.h"

// R�le : Constructeur initialisant le type du mur - Calcule des attributs en fonction
// Entr�es : Le type du mur
// Sortie : Aucune
Wall::Wall(typeWall type) {

	Bounds b;
	type_ = type;

	switch (type) {

	case upWall:
		b.xmin_ = 0.f;
		b.xmax_ = 39.f;
		b.ymin_ = 0.f;
		b.ymax_ = 39.f;
		b.zmin_ = 39.f;
		b.zmax_ = 40.f;
		normal_.x = 0.f;
		normal_.y = 0.f;
		normal_.z = -1.f;
		offset_ = 39.f;
		break;

	case downWall:
		b.xmin_ = 0.f;
		b.xmax_ = 39.f;
		b.ymin_ = 0.f;
		b.ymax_ = 39.f;
		b.zmin_ = -1.f;
		b.zmax_ = 0.f;
		normal_.x = 0.f;
		normal_.y = 0.f;
		normal_.z = 1.f;
		offset_ = 0.f;
		break;

	case rightWall:
		b.xmin_ = 0.f;
		b.xmax_ = 39.f;
		b.ymin_ = 39.f;
		b.ymax_ = 40.f;
		b.zmin_ = 0.f;
		b.zmax_ = 39.f;
		normal_.x = 0.f;
		normal_.y = -1.f;
		normal_.z = 0.f;
		offset_ = 39.f;
		break;

	case leftWall:
		b.xmin_ = 0.f;
		b.xmax_ = 39.f;
		b.ymin_ = -1.f;
		b.ymax_ = 0.f;
		b.zmin_ = 0.f;
		b.zmax_ = 39.f;
		normal_.x = 0.f;
		normal_.y = 1.f;
		normal_.z = 0.f;
		offset_ = 0.f;
		break;

	case frontWall:
		b.xmin_ = 39.f;
		b.xmax_ = 40.f;
		b.ymin_ = 0.f;
		b.ymax_ = 39.f;
		b.zmin_ = 0.f;
		b.zmax_ = 39.f;
		normal_.x = -1.f;
		normal_.y = 0.f;
		normal_.z = 0.f;
		offset_ = 39.f;
		break;

	case behindWall:
		b.xmin_ = -1.f;
		b.xmax_ = 0.f;
		b.ymin_ = 0.f;
		b.ymax_ = 39.f;
		b.zmin_ = 0.f;
		b.zmax_ = 39.f;
		normal_.x = 1.f;
		normal_.y = 0.f;
		normal_.z = 0.f;
		offset_ = 0.f;
		break;

	}

	setBounds(b);
	setOriginalBounds(b);
}

// R�le : Destructeur
// Entr�es : Aucune
// Sortie : Aucune
Wall::~Wall()
{
}

// R�le : Teste si le mur est en collision avec une primitive
// Entr�es : La primitive avec laquelle la collision est test�e
// Sortie : S'il y a collision
bool Wall::isPrimitiveCollidingWith(Primitive* prim)
{
	return prim->isPrimitiveCollidingWith(this);
}

// R�le : Teste si le mur est en collision avec un cube
// Entr�es : Le cube avec lequel la collision est test�e
// Sortie : S'il y a collision
bool Wall::isPrimitiveCollidingWith(Cube* prim)
{
	Vector3D* points = prim->rotatedRepere();

	for (int i = 0; i < 8; i++) {
		float dist = normal_.dotProd(points[i]) + offset_;
		if (dist <= 0) {
			//Affichage des donn�es de la premi�re collision seulement
			if (firstOnly) {
				cout << "-----------------------------------" << endl;
				cout << "Point d'impact: " << points[i].x << ", " << points[i].y << ", " << points[i].z << endl;
				cout << "Normale: " << getNormal().x << ", " << getNormal().y << ", " << getNormal().z << endl;
				cout << "Distance de penetration: " << dist << endl;
				firstOnly = false;
			}
			// Variation de la vitesse
			float vs = prim->getBody()->getVelocity().dotProd(normal_) * prim->getBody()->getInverseMass();
			prim->getBody()->setPosition(prim->getBody()->getPosition() - normal_ * dist);
			prim->getBody()->setVelocity(prim->getBody()->getVelocity() - normal_ * vs);
			// Variation de la vitesse de rotation
			/*
			float d = (points[i] - prim->getBody()->getPosition()).norm() * prim->getBody()->getInverseMass(); //distance entre le point d'impact et le centre du cube
			prim->getBody()->setRotation(prim->getBody()->getRotation() + (prim->getBody()->getVelocity().crossProd(normal_).normalized()) * d);
			*/
			
			return true;
		}
	}

	return false;
}

// R�le : Teste si le mur est en collision avec un autre mur
// Entr�es : Le mur avec lequel la collision est test�e
// Sortie : S'il y a collision
bool Wall::isPrimitiveCollidingWith(Wall* prim)
{
	//not handled
	return false;
}
