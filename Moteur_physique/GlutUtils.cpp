#include "GlutUtils.h"
#include "Color.h"

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
void GlutUtils::drawRectangle(Vector3D pos, Quaternion orientation, float width, float height, float depth, Vector3D color)
{
	glPushMatrix();

	glColor3f(color.x, color.y, color.z);//r�glage couleur
	glTranslatef(pos.x, pos.y, pos.z);//positionnement au centre de l'objet

	glMultMatrixf(orientation.toMatrix3().toMat44());//application de la matrice de rotation

	glBegin(GL_QUADS);//macro openGL pour dessiner des quadrilat�res, que l'on va utiliser 6 fois autour du centre
	//dessin du "haut"
	glVertex3f(-width, -height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(width, height, depth);
	glVertex3f(width, -height, depth);
	//dessin du "bas"
	glVertex3f(-width, -height, -depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	glVertex3f(width, -height, -depth);
	//dessin de la face "droite"
	glVertex3f(-width, -height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(-width, -height, -depth);
	//dessin de "l'arri�re"
	glVertex3f(width, height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	//dessin de la face "gauche"
	glVertex3f(-width, -height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width, -height, -depth);
	glVertex3f(-width, -height, -depth);
	//dessin de "l'avant"
	glVertex3f(width, height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width, -height, -depth);
	glVertex3f(width, height, -depth);

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
	glVertex3f(-width, -height, -depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	glVertex3f(width, -height, -depth);
	//dessin de la face "droite"
	glVertex3f(-width, -height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(-width, -height, -depth);
	//dessin de "l'arri�re"
	glVertex3f(width, height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	//dessin de la face "gauche"
	glVertex3f(-width, -height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width, -height, -depth);
	glVertex3f(-width, -height, -depth);

	glEnd();

	glPopMatrix();
}

void GlutUtils::drawWall(typeWall typeW)
{

	Wall wall = Wall(typeW);
	Vector3D color = Color::darkGray;

	//GlutUtils::drawLine(Vector3D(), wall.bounds_.getCenter(), Color::red);

	Vector3D pos;
	float width;
	float height;
	float depth;
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

	glColor3f(color.x, color.y, color.z);//r�glage couleur
	glTranslatef(pos.x, pos.y, pos.z);//positionnement au centre de l'objet

	glBegin(GL_QUADS);//macro openGL pour dessiner des quadrilat�res, que l'on va utiliser 6 fois autour du centre

					  //dessin du "haut"
	glVertex3f(-depth / 2, -width / 2, height / 2);
	glVertex3f(depth / 2, -width / 2, height / 2);
	glVertex3f(depth / 2, width / 2, height / 2);
	glVertex3f(-depth / 2, width / 2, height / 2);
	//dessin du "bas"
	glVertex3f(-depth / 2, -width / 2, -height / 2);
	glVertex3f(depth / 2, -width / 2, -height / 2);
	glVertex3f(depth / 2, width / 2, -height / 2);
	glVertex3f(-depth / 2, width / 2, -height / 2);
	//dessin de la face "droite"
	glVertex3f(-depth / 2, width / 2, -height / 2);
	glVertex3f(depth / 2, width / 2, -height / 2);
	glVertex3f(depth / 2, width / 2, height / 2);
	glVertex3f(-depth / 2, width / 2, height / 2);
	//dessin de la face "gauche"
	glVertex3f(-depth / 2, -width / 2, -height / 2);
	glVertex3f(depth / 2, -width / 2, -height / 2);
	glVertex3f(depth / 2, -width / 2, height / 2);
	glVertex3f(-depth / 2, -width / 2, height / 2);
	//dessin de "l'avant"
	glVertex3f(depth / 2, -width / 2, -height / 2);
	glVertex3f(depth / 2, width / 2, -height / 2);
	glVertex3f(depth / 2, width / 2, height / 2);
	glVertex3f(depth / 2, -width / 2, height / 2);
	//dessin de "l'arri�re"
	glVertex3f(-depth / 2, -width / 2, -height / 2);
	glVertex3f(-depth / 2, width / 2, -height / 2);
	glVertex3f(-depth / 2, width / 2, height / 2);
	glVertex3f(-depth / 2, -width / 2, height / 2);

	glEnd();

	glPopMatrix();

}
