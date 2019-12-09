#include "GlutUtils.h"

//Dessine une ligne 
void GlutUtils::drawLine(Vector3D a, Vector3D b, Vector3D color)
{
	glPushMatrix();

	glColor3f(color.x, color.y, color.z);//réglage couleur
	glTranslatef(0, 0, 0);//position de dessin en 0

	glBegin(GL_LINES);//macro openGL pour les lignes

	//on indique les deux extrémités
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);

	glEnd();
	glPopMatrix();
}

//Dessine une sphère
void GlutUtils::drawSphere(Vector3D pos, float radius, Vector3D color)
{
	glPushMatrix();

	glColor3f(color.x, color.y, color.z);//réglage couleur
	glTranslatef(pos.x, pos.y, pos.z);//positionnement au centre de la sphère

	//déclaration et utilisation d'une quadrique de openGL pour dessiner la sphère
	GLUquadric* quadrique = gluNewQuadric();
	gluQuadricDrawStyle(quadrique, GLU_FILL);
	gluSphere(quadrique, radius, 20, 20);//on indique le rayon, ainsi que la précision de dessin
	gluDeleteQuadric(quadrique);
	glPopMatrix();
}

//Dessine un parallélépipède rectangle
void GlutUtils::drawRectangle(Vector3D pos, Quaternion orientation, float width, float height, float depth, Vector3D color)
{
	glPushMatrix();

	glColor3f(color.x, color.y, color.z);//réglage couleur
	glTranslatef(pos.x, pos.y, pos.z);//positionnement au centre de l'objet

	glMultMatrixf(orientation.toMatrix3().toMat44());//application de la matrice de rotation

	glBegin(GL_QUADS);//macro openGL pour dessiner des quadrilatères, que l'on va utiliser 6 fois autour du centre
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
	//dessin de "l'arrière"
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

void GlutUtils::drawRectangle(Vector3D* p, Vector3D color)
{
	glPushMatrix();

	Vector3D pivot = p[8];

	glColor3f(color.x, color.y, color.z);//réglage couleur
	glTranslatef(pivot.x, pivot.y, pivot.z);//positionnement au centre de l'objet

	for (int i = 0; i < 8; i++) {
		p[i] = p[i] - pivot;
	}

	glBegin(GL_QUADS);//macro openGL pour dessiner des quadrilatères, que l'on va utiliser 6 fois autour du centre
	//dessin du "haut"
	glVertex3f(p[4].x, p[4].y, p[4].z); //p5
	glVertex3f(p[7].x, p[7].y, p[7].z); //p8
	glVertex3f(p[6].x, p[6].y, p[6].z); //p7
	glVertex3f(p[5].x, p[5].y, p[5].z); //p6
	//dessin du "bas"
	glVertex3f(p[0].x, p[0].y, p[0].z); //p1
	glVertex3f(p[3].x, p[3].y, p[3].z); //p4
	glVertex3f(p[2].x, p[2].y, p[2].z); //p3
	glVertex3f(p[1].x, p[1].y, p[1].z); //p2
	//dessin de la face "droite"
	glVertex3f(p[4].x, p[4].y, p[4].z);  //p5
	glVertex3f(p[7].x, p[7].y, p[7].z); //p8
	glVertex3f(p[3].x, p[3].y, p[3].z); //p4
	glVertex3f(p[0].x, p[0].y, p[0].z); //p1
	//dessin de "l'arrière"
	glVertex3f(p[6].x, p[6].y, p[6].z); //p7
	glVertex3f(p[7].x, p[7].y, p[7].z); //p8
	glVertex3f(p[3].x, p[3].y, p[3].z); //p4
	glVertex3f(p[2].x, p[2].y, p[2].z);  //p3
	//dessin de la face "gauche"
	glVertex3f(p[4].x, p[4].y, p[4].z);  //p5
	glVertex3f(p[5].x, p[5].y, p[5].z);  //p6
	glVertex3f(p[1].x, p[1].y, p[1].z); //p2
	glVertex3f(p[0].x, p[0].y, p[0].z); //p1
	//dessin de "l'avant"
	glVertex3f(p[6].x, p[6].y, p[6].z); //p7
	glVertex3f(p[5].x, p[5].y, p[5].z);  //p6
	glVertex3f(p[1].x, p[1].y, p[1].z); //p2
	glVertex3f(p[2].x, p[2].y, p[2].z); //p3

	glEnd();

	glPopMatrix();
}

//Dessine un parallélépipède rectangle incomplet
void GlutUtils::drawHollowRectangle(Vector3D pos, float width, float height, float depth, Vector3D color)
{
	glColor3f(color.x, color.y, color.z);//réglage couleur
	glTranslatef(pos.x, pos.y, pos.z);//positionnement au centre de l'objet

	glBegin(GL_QUADS);//macro openGL pour dessiner des quadrilatères, que l'on va utiliser 4 fois autour du centre
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
	//dessin de "l'arrière"
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


