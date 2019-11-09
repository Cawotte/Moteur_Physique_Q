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

	static void drawLine(Vector3D a, Vector3D b, Vector3D color);//dessine une ligne avec ses extr�mit�s et sa couleur
	static void drawSphere(Vector3D pos, float radius, Vector3D color);//dessine une sph�re avec son centre, son rayon et sa couleur
	static void drawRectangle(Vector3D pos, float width, float height, float depth, Vector3D color);//dessine un parall�l�pip�de rectangle avec son centre, sa hauteur, sa largeur, sa profondeur et sa couleur
	static void drawHollowRectangle(Vector3D pos, float width, float height, float depth, Vector3D color);//dessine un parall�l�pip�de rectangle de la m�me mani�re, mais avec deux c�t�s en moins, pour voir � l'int�rieur
};

#endif

