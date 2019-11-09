#ifndef GLUT_UTILS
#define GLUT_UTILS

#include "Vector3D.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//Contient des fonctions pour dessiner facilement des formes avec glut et openGL
class GlutUtils
{

public:

	static void drawLine(Vector3D a, Vector3D b, Vector3D color);//dessine une ligne avec ses extrémités et sa couleur
	static void drawSphere(Vector3D pos, float radius, Vector3D color);//dessine une sphère avec son centre, son rayon et sa couleur
	static void drawRectangle(Vector3D pos, float width, float height, float depth, Vector3D color);//dessine un parallélépipède rectangle avec son centre, sa hauteur, sa largeur, sa profondeur et sa couleur
	static void drawHollowRectangle(Vector3D pos, float width, float height, float depth, Vector3D color);//dessine un parallélépipède rectangle de la même manière, mais avec deux côtés en moins, pour voir à l'intérieur
};

#endif

