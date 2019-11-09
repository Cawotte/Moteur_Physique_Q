#ifndef JEU_H
#define JEU_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include <time.h>

#include "Vector3D.h"

// Classe de gestion globale. Dessine la scène, gère les objets, upate la logique et appelle la fonction pour les dessiner
class Game
{
private:


	bool isLeftMouseButtonDown_ = false;


	//pour calculer le framerate variable 
	float elapsedTime;//durée d'une frame : différence entre les deux variables suivantes
	clock_t stopTime = clock();//temps de la nouvelle frame
	clock_t startTime = clock();//temps de la frame précédente

	//dimensions de l'écran
	int screenWidth = 900;
	int screenHeight = 600;

	//reglages camera
	Vector3D posCamera_ = Vector3D(50.0f, -50.f, 5.f); //position de la caméra
	Vector3D lookCamera_ = Vector3D(0.f, 100.f, 15.f); //point regardé par la caméra


	//efface ou affiche le premier plan dessiné de la piscine, pour voir ce qu'il s'y passe dedans
	bool seeInWater_ = true;

public:

	//Glut : intialise l'affichage graphique
	void initRendering();

	//part of hotfix, fait le lien entre les fonctions de callback de glut et celles appelées dans le code pour exécuter l'action appropriée
	void setupInstance();


	//constructor/deconstructor
	Game();
	//~Game();

	// fonctions reliées à Glut et ses callbacks
	void handleKeypress(unsigned char key, int x, int y);//gère l'appui sur une touche
	void handleResize(int w, int h);//gère le redimensionnent de la fenêtre
	void handlePassiveMouseMotion(int x, int y);//gère le déplacement de la souris dans la fenêtre quand un ou plusieurs boutons sont enfoncés
	void handleMouseClick(int button, int state, int x, int y);//gère l'appui sur les boutons de la souris

	//dessine tout ce qu'il faut à l'écran
	void drawScene();

	//// fonctions update
	// global update, appelée à chaque frame pour mettre à jour les entrées, la logique et les sorties
	void update(int value);

	//start the game and write the instructions
	void instructions();//affiche les interactions possibles avec le moteur au lancement de celui-ci
	void execute(int argc, char** argv);//paramètre le moteur et l'affichage, appelé au lancement du programme
	
};

//hotfix car Glut n'apprécie pas l'encapsulation des fonctions comme Reshape/DisplayFunc ect..
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