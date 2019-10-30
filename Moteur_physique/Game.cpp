#include "Game.h"



#pragma region Public Methods 

#pragma region Glut Callbacks



Game::Game()
{
	elapsedTime = 0.f;
}

void Game::handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':

		if (posCamera_.x == 50.f)
		{
			posCamera_ = Vector3D(200.0f, 100.f, 40.f);
			lookCamera_ = Vector3D(-200.f, 100.f, 40.f);
		}
		else if (posCamera_.x == 500.0f)
		{
			posCamera_ = Vector3D(50.0f, -50.f, 5.f);
			lookCamera_ = Vector3D(0.f, 100.f, 15.f);
		}
		else if (posCamera_.x == 200.f)
		{
			posCamera_ = Vector3D(500.0f, 100.f, 0.f);
			lookCamera_ = Vector3D(0.f, 100.f, 0.f);
		}
		break;

	case 'v':
		seeInWater_ = !seeInWater_;
		break;

	//ESCAPE key
	case 27:
		exit(0);
		break;

	default:
		break;
	}
}

void Game::handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glClearColor(0.5, 0.5, 0.5, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 2000.0);

	screenWidth = w;
	screenHeight = h;
}

void Game::handlePassiveMouseMotion(int x, int y) {

	//move reticle toward mouse
	float h = (float)(screenHeight - y - 50);
	Vector3D mouseDirection2D = Vector3D(0.0f, (float)x, h);

}

void Game::handleMouseClick(int button, int state, int x, int y) {

	switch (button) {
		//gestion du tir/chargement du tir
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_UP) {

				//TIREZ!
				isLeftMouseButtonDown_ = false;
			}
			else if (state == GLUT_DOWN) {

				isLeftMouseButtonDown_ = true;
			}
		break;
		//gestion du changement de la particule
		case GLUT_RIGHT_BUTTON:

			if (state == GLUT_DOWN) {

				drawScene();
			}

		break;
	}
}


void Game::drawScene()
{
	//mise a zéro de l'affichage
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posCamera_.x, posCamera_.y, posCamera_.z, 
		lookCamera_.x, lookCamera_.y, lookCamera_.z, 
		0, 0, 1);
	

	glutSwapBuffers();
}

#pragma endregion

// Boucle d'update maintenant à jour les particules et d'autres valeurs.


void Game::update(int value)
{
	//fps
	startTime = stopTime;
	stopTime = clock();
	elapsedTime = ((float)(stopTime - startTime)) / (CLOCKS_PER_SEC);


	//Charge le tir
	if (isLeftMouseButtonDown_) {
		//nein
	}

	drawScene();

	glutPostRedisplay();
	glutTimerFunc((unsigned int)elapsedTime * 1000, updateCallback, 0);
}

//liste d'instructions
void Game::instructions() {
	cout << "##############################################" << endl;
	cout << "# Bienvenue dans le test du moteur physique! #" << endl;
	cout << "##############################################" << endl << endl;
	cout << "Les differentes touches sont:" << endl << endl;
	cout << "Clic gauche pour tirer (il faut rester appuye pour augmenter la puissance)." << endl;
	cout << "Clic droit pour changer de type de projectile." << endl;
	cout << "Touche S pour changer la camera (3 cameras sont disponibles)." << endl;
	cout << "Touche V pour voir dans la piscine." << endl;
	cout << "Touche O pour faire apparaitre une particule directement dans la piscine." << endl;
	cout << "Touche D pour supprimer les particules." << endl;
	cout << "Touche ESCAPE pour quitter le test." << endl;
}




//démarrage du jeu
void Game::execute(int argc, char** argv)
{
	instructions();

	//launch Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);

	glutCreateWindow("Physics Engine");
	initRendering();
	Game::setupInstance();
	glutTimerFunc((unsigned int)elapsedTime, updateCallback, 0);
	glutMainLoop();
}

#pragma endregion


#pragma region Private  Methods 


#pragma region Glut

void Game::initRendering()//initialisation de l'affichage
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1);
}


#pragma endregion


//part of hotfix
void Game::setupInstance() {
	::j_CurrentInstance = this;
	::glutDisplayFunc(::drawSceneCallback);
	::glutReshapeFunc(::handleResizeCallback);
	::glutPassiveMotionFunc(::handlePassiveMouseMotionCallback);
	::glutMouseFunc(::handleMouseClickCallback);
	::glutKeyboardFunc(::handleKeypressCallback);
}


#pragma endregion