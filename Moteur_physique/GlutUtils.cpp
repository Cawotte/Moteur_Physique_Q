#include "GlutUtils.h"

//Dessine une ligne 
void GlutUtils::drawLine(Vector3D a, Vector3D b, Vector3D color)
{
	glPushMatrix();

	glColor3f(color.x, color.y, color.z);//r�glage couleur
	glTranslatef(0, 0, 0);//position de dessin en 0

	glBegin(GL_LINES);//macro openGL pour les lignes

	//on indique les deux extr�mit�s
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	glEnd();
	glPopMatrix();
}

//Dessine une sph�re
void GlutUtils::drawSphere(Vector3D pos, float radius, Vector3D color)
{
	glPushMatrix();

	glColor3f(color.x, color.y, color.z);//r�glage couleur
	glTranslatef(pos.x, pos.y, pos.z);//positionnement au centre de la sph�re

	//d�claration et utilisation d'une quadrique de openGL pour dessiner la sph�re
	GLUquadric* quadrique = gluNewQuadric();
	gluQuadricDrawStyle(quadrique, GLU_FILL);
	gluSphere(quadrique, radius, 20, 20);//on indique le rayon, ainsi que la pr�cision de dessin
	gluDeleteQuadric(quadrique);
	glPopMatrix();
}

//Dessine un parall�l�pip�de rectangle
void GlutUtils::drawRectangle(Vector3D pos, float width, float height, float depth, Vector3D color)
{
	glPushMatrix();

	glColor3f(color.x, color.y, color.z);//r�glage couleur
	glTranslatef(pos.x, pos.y, pos.z);//positionnement au centre de l'objet

	glBegin(GL_QUADS);//macro openGL pour dessiner des quadrilat�res, que l'on va utiliser 6 fois autour du centre
	//dessin du "haut"
	glVertex3f(-width / 2, -height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(width / 2, height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, depth / 2);
	//dessin du "bas"
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	//dessin de la face "droite"
	glVertex3f(-width / 2, -height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	//dessin de "l'arri�re"
	glVertex3f(width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, height / 2, -depth / 2);
	//dessin de la face "gauche"
	glVertex3f(-width / 2, -height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	//dessin de "l'avant"
	glVertex3f(width / 2, height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	glVertex3f(width / 2, height / 2, -depth / 2);

	glEnd();

	glPopMatrix();
}

//Dessine un parall�l�pip�de rectangle incomplet
void GlutUtils::drawHollowRectangle(Vector3D pos, float width, float height, float depth, Vector3D color)
{
	glColor3f(color.x, color.y, color.z);//r�glage couleur
	glTranslatef(pos.x, pos.y, pos.z);//positionnement au centre de l'objet

	glBegin(GL_QUADS);//macro openGL pour dessiner des quadrilat�res, que l'on va utiliser 4 fois autour du centre
	//dessin du "bas"
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	//dessin de la face "droite"
	glVertex3f(-width / 2, -height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	//dessin de "l'arri�re"
	glVertex3f(width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, height / 2, -depth / 2);
	//dessin de la face "gauche"
	glVertex3f(-width / 2, -height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	glVertex3f(-width / 2, -height / 2, -depth / 2);

	glEnd();

	glPopMatrix();
}


