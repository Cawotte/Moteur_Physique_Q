﻿#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>     
#include <time.h>

#include "Game.h"
#include "Quaternion.h"
#include <math.h>

int main(int argc, char** argv) {

	Game jeu;
	jeu.execute(argc, argv);

}