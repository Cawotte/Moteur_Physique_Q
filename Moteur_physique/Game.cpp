#include "Game.h"



#pragma region Public Methods 

#pragma region Glut Callbacks


//Constructeur. Appelé au démarrage. Indique que le temps de la frame précédente (qui n'existe en réalité pas) est de 0
Game::Game()
{
	elapsedTime = 0.f;
}

//Gestion de l'appui sur une touche du clavier
void Game::handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's'://touche 's' : change le point de vue de la caméra
		//selon l'angle de vue courant, on passe au suivant, en changeant la position et la direction de regard de la caméra
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

	case 'v'://touche 'v' : permet de voir/cacher l'intérieur de la piscine
		seeInWater_ = !seeInWater_;
		break;

	
	case 27://touche echap : ferme le programme
		exit(0);
		break;

	default:
		break;
	}
}

//Gère le redimensionnement de la fenêtre : redessine le fond et repositionne la caméra. Le reste est redessiné automatique correctement à la frame suivante
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

//Permet de suivre la position de la souris quand on clique, donc adapter la direction de tir de l'objet
void Game::handlePassiveMouseMotion(int x, int y) {
	//move reticle toward mouse
	float h = (float)(screenHeight - y - 50);
	Vector3D mouseDirection2D = Vector3D(0.0f, (float)x, h);
}

//Gestion d'un clic sur la souris
void Game::handleMouseClick(int button, int state, int x, int y) {

	switch (button) {//selon le bouton cliqué
		
		case GLUT_LEFT_BUTTON://si c'est le bouton gauche : gestion du tir/chargement du tir
			if (state == GLUT_UP) {//si on soulève/arrête le clic : on tire
				//TIREZ!
				isLeftMouseButtonDown_ = false;
			}
			else if (state == GLUT_DOWN) {//si on appuie/commence le clic : on commence le chargement du tir

				isLeftMouseButtonDown_ = true;
			}
		break;
		
		case GLUT_RIGHT_BUTTON://si c'est le bouton droit : gestion du changement de la particule
			if (state == GLUT_DOWN) {//si on appuie : on change la particule à tirer
				drawScene();
			}

		break;
	}
}

//Dessin de tout ce qui est affiché à l'écran
void Game::drawScene()
{
	//mise a zéro de l'affichage, réglage des paramètres d'OpenGL
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//vide les buffers de couleur et de profondeur
	glClearColor(0.5, 0.5, 0.5, 1);//maj de la couleur de fond
	glMatrixMode(GL_MODELVIEW);//mode de réglage du point de vue
	glLoadIdentity();//raz du point de vue
	gluLookAt(posCamera_.x, posCamera_.y, posCamera_.z, 
		lookCamera_.x, lookCamera_.y, lookCamera_.z, 
		0, 0, 1);//réglage de la caméra
	

	glutSwapBuffers();
}

#pragma endregion

// Boucle d'update maintenant à jour les objets et d'autres valeurs.
void Game::update(int value)
{
	//calcul de la durée de la dernière frame
	startTime = stopTime;
	stopTime = clock();
	elapsedTime = ((float)(stopTime - startTime)) / (CLOCKS_PER_SEC);


	//Charge le tir si le clic est enclenché
	if (isLeftMouseButtonDown_) {
		//nein
	}

	//dessine à l'écran
	drawScene();

	glutPostRedisplay();//indique qu'il faut redessiner à la frame suivante
	glutTimerFunc((unsigned int)elapsedTime * 1000, updateCallback, 0);//gestion de la durée de la frame
}

//liste des interactions possibles avec le moteur affichée dans la console au lancement
void Game::instructions() {
	cout << "##############################################" << endl;
	cout << "# Bienvenue dans le test du moteur physique! #" << endl;
	cout << "##############################################" << endl << endl;
}




//démarrage du jeu : paramétrage de glut pour le bon fonctionnement du moteur - on a suivi ce qu'on a trouvé dans les exemples sur internet
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
	glEnable(GL_DEPTH_TEST);//permet de dessiner avec prise en compte de la profondeur
	glClearColor(0.5, 0.5, 0.5, 1);//initialisation de la couleur de fond
}


#pragma endregion


//part of hotfix pour l'encapsulation des fonctions de callback/interactions avec l'utilisateur
void Game::setupInstance() {
	::j_CurrentInstance = this;
	::glutDisplayFunc(::drawSceneCallback);
	::glutReshapeFunc(::handleResizeCallback);
	::glutPassiveMotionFunc(::handlePassiveMouseMotionCallback);
	::glutMouseFunc(::handleMouseClickCallback);
	::glutKeyboardFunc(::handleKeypressCallback);
}


#pragma endregion