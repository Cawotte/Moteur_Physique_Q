#include "GlutUtils.h"
#include "Color.h"

// Rôle : Dessine une ligne 
// Entrées : Les extrémités et la couleur de la ligne
// Sortie : Aucune
void GlutUtils::drawLine(Vector3D a, Vector3D b, Vector3D color)
{
	glPushMatrix();
	//Réglage couleur
	glColor3f(color.x, color.y, color.z);
	//Position de dessin en 0
	glTranslatef(0, 0, 0);
	//Macro openGL pour les lignes
	glBegin(GL_LINES);

	//On indique les deux extrémités
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	glEnd();
	glPopMatrix();
}

// Rôle : Dessine une sphère
// Entrées : Le centre, le rayon et la couleur
// Sortie : Aucune
void GlutUtils::drawSphere(Vector3D pos, float radius, Vector3D color)
{
	glPushMatrix();
	//Réglage couleur
	glColor3f(color.x, color.y, color.z);
	//Positionnement au centre de la sphère
	glTranslatef(pos.x, pos.y, pos.z);

	//Déclaration et utilisation d'une quadrique de openGL pour dessiner la sphère
	GLUquadric* quadrique = gluNewQuadric();
	gluQuadricDrawStyle(quadrique, GLU_FILL);
	//On indique le rayon, ainsi que la précision de dessin
	gluSphere(quadrique, radius, 20, 20);
	gluDeleteQuadric(quadrique);
	glPopMatrix();
}

// Rôle : Dessin un parallélépipède rectangle
// Entrées : La position, l'orientation, les demi-dimensions, la couleur
// Sortie : Aucune
void GlutUtils::drawRectangle(Vector3D pos, Quaternion orientation, float width, float height, float depth, Vector3D color)
{
	glPushMatrix();
	//Réglage couleur
	glColor3f(color.x, color.y, color.z);
	//Positionnement au centre de l'objet
	glTranslatef(pos.x, pos.y, pos.z);
	//Application de la matrice de rotation
	glMultMatrixf(orientation.toMatrix3().toMat44());
	//Macro openGL pour dessiner des quadrilatères, que l'on va utiliser 6 fois autour du centre
	glBegin(GL_QUADS);
	//Dessin du "haut"
	glVertex3f(-width, -height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(width, height, depth);
	glVertex3f(width, -height, depth);
	//Dessin du "bas"
	glVertex3f(-width, -height, -depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	glVertex3f(width, -height, -depth);
	//Dessin de la face "droite"
	glVertex3f(-width, -height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(-width, -height, -depth);
	//Dessin de "l'arrière"
	glVertex3f(width, height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	//Dessin de la face "gauche"
	glVertex3f(-width, -height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width, -height, -depth);
	glVertex3f(-width, -height, -depth);
	//Dessin de "l'avant"
	glVertex3f(width, height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width, -height, -depth);
	glVertex3f(width, height, -depth);

	glEnd();

	glPopMatrix();
}

// Rôle : Dessine un parallélépipède rectangle incomplet
// Entrées : La position, l'orientation, les demi-dimensions, la couleur
// Sortie : Aucune
void GlutUtils::drawHollowRectangle(Vector3D pos, float width, float height, float depth, Vector3D color)
{
	//Réglage couleur
	glColor3f(color.x, color.y, color.z);
	//Positionnement au centre de l'objet
	glTranslatef(pos.x, pos.y, pos.z);
	//Macro openGL pour dessiner des quadrilatères, que l'on va utiliser 4 fois autour du centre
	glBegin(GL_QUADS);
	//Dessin du "bas"
	glVertex3f(-width, -height, -depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	glVertex3f(width, -height, -depth);
	//Dessin de la face "droite"
	glVertex3f(-width, -height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(-width, -height, -depth);
	//Dessin de "l'arrière"
	glVertex3f(width, height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	//Dessin de la face "gauche"
	glVertex3f(-width, -height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width, -height, -depth);
	glVertex3f(-width, -height, -depth);

	glEnd();

	glPopMatrix();
}

// Rôle : Dessine un mur
// Entrées : Le type du mur : lequel dessiner
// Sortie : Aucune
void GlutUtils::drawWall(typeWall typeW)
{
	//Réglage couleur
	Vector3D color = Color::darkGray;

	//Position du mur à dessiner
	Vector3D pos;
	//Dimensions du mur
	float width;
	float height;
	float depth;
	//Selon le type de mur, on initialise la position et les dimensions de ce dernier
	switch (typeW) {

	case upWall:
		pos.x = 19.5f;
		pos.y = 19.5f;
		pos.z = 39.5f;
		height = 1.f;
		depth = 39.f;
		width = 39.f;
		break;

	case downWall:
		pos.x = 19.5f;
		pos.y = 19.5f;
		pos.z = -0.5f;
		height = 1.f;
		depth = 39.f;
		width = 39.f;
		break;

	case rightWall:
		pos.x = 19.5f;
		pos.y = 39.5f;
		pos.z = 19.5f;
		height = 39.f;
		depth = 39.f;
		width = 1.f;
		break;

	case leftWall:
		pos.x = 19.5f;
		pos.y = -0.5f;
		pos.z = 19.5f;
		height = 39.f;
		depth = 39.f;
		width = 1.f;
		break;

	case frontWall:
		pos.x = 39.5f;
		pos.y = 19.5f;
		pos.z = 19.5f;
		height = 39.f;
		depth = 1.f;
		width = 39.f;
		break;

	case behindWall:
		pos.x = -0.5f;
		pos.y = 19.5f;
		pos.z = 19.5f;
		height = 39.f;
		depth = 1.f;
		width = 39.f;
		break;

	}
	glPushMatrix();
	//Réglage couleur
	glColor3f(color.x, color.y, color.z);
	//Positionnement au centre de l'objet
	glTranslatef(pos.x, pos.y, pos.z);
	//Macro openGL pour dessiner des quadrilatères, que l'on va utiliser 6 fois autour du centre
	glBegin(GL_QUADS);

	//Dessin du "haut"
	glVertex3f(-depth / 2, -width / 2, height / 2);
	glVertex3f(depth / 2, -width / 2, height / 2);
	glVertex3f(depth / 2, width / 2, height / 2);
	glVertex3f(-depth / 2, width / 2, height / 2);
	//Dessin du "bas"
	glVertex3f(-depth / 2, -width / 2, -height / 2);
	glVertex3f(depth / 2, -width / 2, -height / 2);
	glVertex3f(depth / 2, width / 2, -height / 2);
	glVertex3f(-depth / 2, width / 2, -height / 2);
	//Dessin de la face "droite"
	glVertex3f(-depth / 2, width / 2, -height / 2);
	glVertex3f(depth / 2, width / 2, -height / 2);
	glVertex3f(depth / 2, width / 2, height / 2);
	glVertex3f(-depth / 2, width / 2, height / 2);
	//Dessin de la face "gauche"
	glVertex3f(-depth / 2, -width / 2, -height / 2);
	glVertex3f(depth / 2, -width / 2, -height / 2);
	glVertex3f(depth / 2, -width / 2, height / 2);
	glVertex3f(-depth / 2, -width / 2, height / 2);
	//Dessin de "l'avant"
	glVertex3f(depth / 2, -width / 2, -height / 2);
	glVertex3f(depth / 2, width / 2, -height / 2);
	glVertex3f(depth / 2, width / 2, height / 2);
	glVertex3f(depth / 2, -width / 2, height / 2);
	//Dessin de "l'arrière"
	glVertex3f(-depth / 2, -width / 2, -height / 2);
	glVertex3f(-depth / 2, width / 2, -height / 2);
	glVertex3f(-depth / 2, width / 2, height / 2);
	glVertex3f(-depth / 2, -width / 2, height / 2);

	glEnd();

	glPopMatrix();

}
