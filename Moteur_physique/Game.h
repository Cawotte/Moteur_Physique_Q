#ifndef JEU_H
#define JEU_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include <time.h>

#include "Vector3D.h"

// Classe de gestion globale. Dessine la scène, gère les particules, upate la logique et appelle leur fonction pour les dessiner
class Game
{
private:


	bool isLeftMouseButtonDown_ = false;


	//time
	float elapsedTime;
	clock_t stopTime = clock();
	clock_t startTime = clock();

	//dimensions de l'écran
	int screenWidth = 900;
	int screenHeight = 600;

	//reglages camera
	Vector3D posCamera_ = Vector3D(50.0f, -50.f, 5.f);
	Vector3D lookCamera_ = Vector3D(0.f, 100.f, 15.f);


	//pour voir dans la piscine
	bool seeInWater_ = true;

public:

	//Glut
	void initRendering();



	//part of hotfix
	void setupInstance();


	//constructor/deconstructor
	Game();
	//~Game();

	// fonctions reliées à Glut et ses callbacks
	void handleKeypress(unsigned char key, int x, int y);
	void handleResize(int w, int h);
	void handlePassiveMouseMotion(int x, int y);
	void handleMouseClick(int button, int state, int x, int y);

	//fonctions draw
	void drawScene();

	//// fonctions update
	// global update
	void update(int value);

	//start the game and write the instructions
	void instructions();
	void execute(int argc, char** argv);
	
};

//hotfix because Glut doesn't like encapsulated call to Reshape/DisplayFunc ect..
static Game* j_CurrentInstance;

extern "C"
static void drawSceneCallback() {
	j_CurrentInstance->drawScene();
}
static void handleResizeCallback(int w, int h) {
	j_CurrentInstance->handleResize(w, h);
}

static void handlePassiveMouseMotionCallback(int x, int y) {
	j_CurrentInstance->handlePassiveMouseMotion(x, y);
}

static void handleMouseClickCallback(int button, int state, int x, int y) {
	j_CurrentInstance->handleMouseClick(button, state, x, y);
}

static void handleKeypressCallback(unsigned char key, int x, int y) {
	j_CurrentInstance->handleKeypress(key, x, y);
}

static void updateCallback(int value) {
	j_CurrentInstance->update(value);
}

#endif