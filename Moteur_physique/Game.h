#ifndef JEU_H
#define JEU_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <list>
#include <vector>
#include <time.h>

#include "Vector3D.h"
#include "Box.h"
#include "ForceRegister.h"
#include "GravityFG.h"
#include "Octree.h"
#include "Primitive.h"
#include "Wall.h"
#include "ContactResolver.h"
#include "Cube.h"

// Classe de gestion globale. Dessine la scène, gère les objets, upate la logique et appelle la fonction pour les dessiner
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nom : Game
// But : Gestion globale
//		 Gère la boucle de jeu
//		 Dessine la scène, gère les objets, upate la logique et appelle la fonction pour les dessiner
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Game
{
private:

	//Objets
	list<Box*> bodies_;//liste de base utilisée pour stocker les bodies

	//Résolution des contacts
	ContactResolver contactResolver_;

	//int pour les 3 types de rotation pour le premier test
	int typeRotation_ = 0;

	//int pour la vue des murs (0 = pas de murs, 1 = les murs du fond et 2 = tous les murs)
	int vueWalls_ = 0;

	//registre pour les forces
	ForceRegister register_;

	//Constantes
	Vector3D g_ = Vector3D(0, 0, -9.8f);


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

public:

	//Glut : initialise l'affichage graphique
	void initRendering();

	//part of hotfix, fait le lien entre les fonctions de callback de glut et celles appelées dans le code pour exécuter l'action appropriée
	void setupInstance();

	//Constructeur
	Game();
	//Destructeur
	~Game();

	//Fonctions reliées à Glut et ses callbacks
	//Gère l'appui sur une touche
	void handleKeypress(unsigned char key, int x, int y);
	//Gère le redimensionnent de la fenêtre
	void handleResize(int w, int h);
	
	//Dessine l'intégralité de la scène
	void drawScene();

	//Dessine les rigid bodies
	void drawBodies();

	//Dessine tous les murs
	void drawWalls();

	//Ajoute un RigidBody à la liste des bodies
	void addBody(Box* rb);

	//Retire un RigidBody à la liste des bodies
	void deleteBody(Box* rb);

	//Supprime tous les bodies de la liste
	void deleteAllBodies();

	//Supprimer tous les éléments contenus dans la scène
	void deleteAndClearAll();

	//Ajoute les 6 murs de la pièce à la liste des primitives
	void createWalls();

	//Applique les forces sur les boxs de bodies_
	void applyRegister(float time);

	//Applique les mouvements sur les boxs de bodies_
	void applyMovements(float time);

	//Applique les collisons sur les boxs de bodies_
	void applyCollisions(float time);

	//Update global, appelée à chaque frame pour mettre à jour les entrées, la logique et les sorties : boucle de jeu
	void update(int value);

	//Démarrent le jeu
	//Affiche les interactions possibles avec le moteur au lancement de celui-ci	
	void instructions();
	//Paramètre le moteur et l'affichage, appelé au lancement du programme
	void execute(int argc, char** argv);	
};

//Hotfix car Glut n'apprécie pas l'encapsulation des fonctions comme Reshape/DisplayFunc ect..
static Game* j_CurrentInstance;

extern "C"
static void drawSceneCallback() {
	j_CurrentInstance->drawScene();
}
static void handleResizeCallback(int w, int h) {
	j_CurrentInstance->handleResize(w, h);
}

static void handleKeypressCallback(unsigned char key, int x, int y) {
	j_CurrentInstance->handleKeypress(key, x, y);
}

static void updateCallback(int value) {
	j_CurrentInstance->update(value);
}

#endif