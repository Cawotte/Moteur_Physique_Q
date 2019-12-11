#include "Game.h"

#pragma region Public Methods 

#pragma region Glut Callbacks


// Rôle : Constructeur - Initialise l'objet
// Entrées : Valeurs des extrémités de l'objet associé
// Sortie : Aucune
Game::Game()
{
	//Initialisation pour l'aléatoire
	srand(unsigned int(time(NULL)));
	//Mise à zéro du temps de la frame précédente (qui n'existe pas en réalité)
	elapsedTime = 0.f;
	//Crée les murs
	createWalls();
}

// Rôle : Destructeur - Vide les listes et détruit l'objet
// Entrées : Aucune
// Sortie : Aucune
Game::~Game() {
	deleteAllBodies();
	register_.clear();
	contactResolver_.clear();
}

//Gestion de l'appui sur une touche du clavier
// Rôle : Gère l'appui sur une touche
// Entrées : code de la touche appuyée, coordonnées de la souris au moment où la touche est pressée
// Sortie : Aucune
void Game::handleKeypress(unsigned char key, int x, int y)
{
	//Les variables sont déclarées ici car elle ne peuvent pas l'être à l'intérieur du switch
	//Box utilisée lors de l'appui sur la touche B
	Box * b = NULL;
	//Itérateur pour parcourir une liste de primitives
	std::list<Primitive*>::iterator it;
	//coordonnées xyz tirées au sort pour l'apparition des boxs lors de l'appui sur la touche T
	int xxx;
	int yyy;
	int zzz;
	//demi-dimensions des boites utilisées lors de l'appui sur la touche T
	float sizeBox = 2.f;
	//dimension de la zone dans laquelle on teste les collisions
	int areaBox = 41;

	switch (key)
	{
		//Touche 's' : change le point de vue de la caméra
		case 's':
			//Selon l'angle de vue courant, on passe au suivant, en changeant la position et la direction de regard de la caméra
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
		//Touche 'b' : lance une box
		case 'b':
			b = new Box(100.0f, Vector3D(5.f, 5.f, 5.f), Quaternion(1., 0., 0., 0.f), 0.99f, 0.99f, 2.5f, 2.5f, 2.5f);
			b->setVelocity(Vector3D(10.f, 50.f, 20.f));
			//Alternance de trois types de rotation (et par conséquent de couleur pour les différencier)
			if (typeRotation_ == 0) {
				b->setRotation(Vector3D(3.f, 3.f, 0.f));
			}else if (typeRotation_ == 1) {
				b->setRotation(Vector3D(0.f, 3.f, 3.f));
				b->setColor(Color::orange);
			}
			else if (typeRotation_ == 2) {
				b->setRotation(Vector3D(3.f, 0.f, 3.f));
				b->setColor(Color::purple);
			}
			typeRotation_ += 1;
			typeRotation_ %= 3;
			//On ajoute la primitive associée à la liste + la box à la liste
			contactResolver_.addPrimitive(new Cube(b, Bounds(5.f - 2.5f, 5.f + 2.5f, 5.f - 2.5f, 5.f + 2.5f, 5.f - 2.5f, 5.f + 2.5f)));
			addBody(b);
			break;
		//Touche 't' : fait apparaitre un cube dans la zone -1/40 en x/y/z
		case 't':
			//Tirage des valeurs de x/y/z
			xxx = rand() % (areaBox) - 1;
			yyy = rand() % (areaBox) - 1;
			zzz = rand() % (areaBox) - 1;
			//Création de la boite à la position tirée
			b = new Box(100.f, Vector3D(float(xxx), float(yyy), float(zzz)), Quaternion(1., 0., 0., 0.f), 0.99f, 0.99f, 0.5f, 0.5f, 0.5f);
			//velocite et rotation nulle pour la boite : test en statique
			b->setVelocity(Vector3D(0.f, 0.f, 0.f));
			b->setRotation(Vector3D(0.f, 0.f, 0.f));
			b->setColor(Color::green);
			//On ajoute la primitive associée à la liste + la box à la liste
			contactResolver_.addPrimitive(new Cube(b, Bounds(xxx - sizeBox, xxx + sizeBox, yyy - sizeBox, yyy + sizeBox, zzz - sizeBox, zzz + sizeBox)));;
			addBody(b);
			break;
		//Touche 'm' : broad phase manuelle
		case 'm':
			contactResolver_.broadPhase();
			contactResolver_.displayBroadPhase();
			break;
		//Touche 'v' : affiche ou non les murs
		case 'v':
			vueWalls_ += 1;
			vueWalls_ %= 4;
			break;
		//Touche 'd' : vide la scène des boîtes
		case 'd':
			deleteAndClearAll();
			break;
		//touche 'echap' : ferme le programme
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

// Rôle : Gère le redimensionnement de la fenêtre : redessine le fond et repositionne la caméra. Le reste est redessiné automatique correctement à la frame suivante
// Entrées : Nouvelles dimensions de la fenêtre
// Sortie : Aucune
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

// Rôle : Applique les forces sur les boxs de bodies_
// Entrées : Durée de la dernière frame
// Sortie : Aucune
void Game::applyRegister(float time) {

	std::list<Box*>::iterator it;

	//Register bodies
	for (it = bodies_.begin(); it != bodies_.end(); it++)
	{
		//Ajoute la gravité pour chaque box dans bodies_
		register_.add(*it, new GravityFG(g_));
	}
	//Applique toutes les forces dans le registre
	register_.updateForces(time);
	//Vide le registre
	register_.clear();
}

// Rôle : Applique les mouvements sur les boxs de bodies_
// Entrées : Durée de la dernière frame
// Sortie : Aucune
void Game::applyMovements(float time) {

	std::list<Box*>::iterator it;

	//Update la physique pour chaque box dans bodies_
	for (it = bodies_.begin(); it != bodies_.end(); it++)
	{
		//Vérifie que la particule n'est pas nulle
		if (*it != NULL) {
			//Calcule la nouvelle position de la box
			(*it)->integrate(time);
		}
	}
}

// Rôle : Applique les collisions sur les boxs de bodies_
// Entrées : Durée de la dernière frame
// Sortie : Aucune
void Game::applyCollisions(float time)
{
	//BroadPhase
	contactResolver_.broadPhase();
	
	//NarrowPhase
	int lastNumberCollisions = contactResolver_.narrowPhase();
	contactResolver_.setNumCollisions(2 * lastNumberCollisions);
	while (contactResolver_.getNumCollisions() > 0 && lastNumberCollisions != 0) {
		lastNumberCollisions = contactResolver_.narrowPhase();
		contactResolver_.setNumCollisions(contactResolver_.getNumCollisions() - lastNumberCollisions);
	}
	contactResolver_.setNumCollisions(0);
}

// Rôle : Dessine les boxs de bodies_
// Entrées : Aucune
// Sortie : Aucune
void Game::drawBodies() {
	std::list<Box*>::iterator it;
	for (it = bodies_.begin(); it != bodies_.end(); it++)
	{
		if (*it != NULL) {
			//Pour chaque box de bodies_, si elle n'est pas nulle, appel de la fonction qui la dessine
			(*it)->display();
		}
	}

}

// Rôle : Dessine les murs
// Entrées : Aucune
// Sortie : Aucune
void Game::drawWalls() {
	switch (vueWalls_) {
	case 0:
		GlutUtils::drawWall(typeWall::rightWall);
		break;
	case 1:
		GlutUtils::drawWall(typeWall::rightWall);
		GlutUtils::drawWall(typeWall::behindWall);
		GlutUtils::drawWall(typeWall::downWall);
		break;
	case 2:
		GlutUtils::drawWall(typeWall::rightWall);
		GlutUtils::drawWall(typeWall::behindWall);
		GlutUtils::drawWall(typeWall::downWall);
		GlutUtils::drawWall(typeWall::frontWall);
		GlutUtils::drawWall(typeWall::leftWall);
		GlutUtils::drawWall(typeWall::upWall);
		break;
	case 3:
		break;
	default:
		break;
	}
}

// Rôle : Dessine l'intégralité de la scène
// Entrées : Aucune
// Sortie : Aucune
void Game::drawScene()
{
	//Mise a zéro de l'affichage, réglage des paramètres d'OpenGL
	//Vide les buffers de couleur et de profondeur
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Maj de la couleur de fond
	glClearColor(0.5, 0.5, 0.5, 1);
	//Mode de réglage du point de vue
	glMatrixMode(GL_MODELVIEW);
	//Raz du point de vue
	glLoadIdentity();
	//Réglage de la caméra
	gluLookAt(posCamera_.x, posCamera_.y, posCamera_.z, 
		lookCamera_.x, lookCamera_.y, lookCamera_.z, 
		0, 0, 1);

	//Dessine les murs
	drawWalls();

	//Dessine les boxs de bodies_
	drawBodies();

	glutSwapBuffers();
}

#pragma endregion

// Rôle : Boucle d'update maintenant à jour les objets et d'autres valeurs
// Entrées : Paramètre par défaut de la fonction - non utilisé
// Sortie : Aucune
void Game::update(int value)
{
	//Calcul de la durée de la dernière frame
	startTime = stopTime;
	stopTime = clock();
	elapsedTime = ((float)(stopTime - startTime)) / (CLOCKS_PER_SEC);

	//Applique les forces, les mouvements puis les collisions sur les boxs
	applyRegister(elapsedTime);
	applyMovements(elapsedTime);
	applyCollisions(elapsedTime);

	//Dessine à l'écran
	drawScene();

	glutPostRedisplay();//indique qu'il faut redessiner à la frame suivante
	glutTimerFunc((unsigned int)elapsedTime * 1000, updateCallback, 0);//gestion de la durée de la frame
}

// Rôle : Affiche les interactions possibles avec le moteur au lancement de celui-ci
// Entrées : Aucune
// Sortie : Aucune
void Game::instructions() {
	cout << "##############################################" << endl;
	cout << "# Bienvenue dans le test du moteur physique! #" << endl;
	cout << "##############################################" << endl << endl;
	cout << "La touche S sert a changer la camera." << endl;
	cout << "La touche B sert a lancer une boite (l'axe change a chaque fois)." << endl;
	cout << "La touche V sert a changer la quantite de murs." << endl;
	cout << "La touche T sert a ajouter un cube avec une position aleatoire dans la zone [-1, 40]." << endl;
	cout << "La touche M sert a lancer une broadphase manuelle." << endl;
	cout << "La touche D sert a supprimer les objets ajoutes par l'utilisateur." << endl;
}

// Rôle : Ajoute un RigidBody à la liste des bodies
// Entrées : La box à ajouter au vecteur
// Sortie : Aucune
void Game::addBody(Box* rb) {
	bodies_.push_back(rb);
}

// Rôle : Retire un RigidBody à la liste des bodies
// Entrées : La box à retirer du vecteur
// Sortie : Aucune
void Game::deleteBody(Box* rb) {
	bodies_.remove(rb);
	delete(rb);
}

// Rôle : Supprime tous les bodies de la liste
// Entrées : Aucune
// Sortie : Aucune
void Game::deleteAllBodies() {
	while (!bodies_.empty())
		deleteBody(bodies_.front());
}

// Rôle : Supprimer tous les éléments contenus dans la scène
// Entrées : Aucune
// Sortie : Aucune
void Game::deleteAndClearAll() {
	//Supprime toutes les boxs
	deleteAllBodies();
	//Vide le registre de forces
	register_.clear();
	//Vide le registre des contacts
	contactResolver_.clear();
	//Recrée les murs de la pièce
	createWalls();
}

// Rôle : Ajoute les 6 murs de la pièce à la liste des primitives
// Entrées : Aucune
// Sortie : Aucune
void Game::createWalls() {
	switch (vueWalls_) {
	case 0:
		contactResolver_.addPrimitive(new Wall(typeWall::rightWall));
		break;
	case 1:
		contactResolver_.addPrimitive(new Wall(typeWall::rightWall));
		contactResolver_.addPrimitive(new Wall(typeWall::behindWall));
		contactResolver_.addPrimitive(new Wall(typeWall::downWall));
		break;
	case 2:
		contactResolver_.addPrimitive(new Wall(typeWall::rightWall));
		contactResolver_.addPrimitive(new Wall(typeWall::upWall));
		contactResolver_.addPrimitive(new Wall(typeWall::downWall));
		contactResolver_.addPrimitive(new Wall(typeWall::leftWall));
		contactResolver_.addPrimitive(new Wall(typeWall::frontWall));
		contactResolver_.addPrimitive(new Wall(typeWall::behindWall));
		break;
	case 3:
		break;
	default:
		break;
	}
}

// Rôle : Paramètre le moteur et l'affichage, appelé au lancement du programme
// Entrées : Paramètres par défaut
// Sortie : Aucune
void Game::execute(int argc, char** argv)
{
	instructions();

	//Lance Glut
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

// Rôle : Glut - initialise l'affichage graphique
// Entrées : Aucune
// Sortie : Aucune
void Game::initRendering()
{
	//Permet de dessiner avec prise en compte de la profondeur
	glEnable(GL_DEPTH_TEST);
	//Initialisation de la couleur de fond
	glClearColor(0.5, 0.5, 0.5, 1);
}


#pragma endregion

// Rôle : Partie de hotfix pour l'encapsulation des fonctions de callback/interactions avec l'utilisateur
// Entrées : Aucune
// Sortie : Aucune
void Game::setupInstance() {
	::j_CurrentInstance = this;
	::glutDisplayFunc(::drawSceneCallback);
	::glutReshapeFunc(::handleResizeCallback);
	::glutKeyboardFunc(::handleKeypressCallback);
}


#pragma endregion