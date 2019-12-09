#include "Game.h"

#pragma region Public Methods 

#pragma region Glut Callbacks


//Constructeur. Appelé au démarrage. Indique que le temps de la frame précédente (qui n'existe pas en réalité) est de 0
Game::Game()
{
	srand(unsigned int(time(NULL)));
	elapsedTime = 0.f;
}

//Gestion de l'appui sur une touche du clavier
void Game::handleKeypress(unsigned char key, int x, int y)
{
	Box * b = NULL;

	std::list<Primitive*>::iterator it;
	int xxx;
	int yyy;
	int zzz;
	float sizeBox;
	int areaBox;

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

	case 'b'://touche 'b' : lance une box
		b = new Box(100.0f, Vector3D(0.f, 0.f, 5.f), Quaternion(1., 0., 0., 0.f), 0.99f, 0.99f, 5.f, 20.f, 5.f);
		b->setVelocity(Vector3D(0.f, 50.f, 20.f));
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
		//on ajoute la primitive associée à la liste + la box à la liste
		primitives_.push_back(new Primitive(b, Bounds(0.f - 2.5f, 0.f + 2.5f, 0.f - 10.f, 0.f + 10.f, 5.f - 2.5f, 5.f + 2.5f)));
		addBody(b);
		break;

	case 't'://touche 't' : fait apparaitre un cube dans la zone -1/40 en x/y/z

		sizeBox = 2.f; //0.5f
		areaBox = 1; //41
		//tirage des valeurs de x/y/z
		xxx = rand() % (areaBox) -1;
		yyy = rand() % (areaBox) - 1;
		zzz = rand() % (areaBox) - 1;
		//création de la boite à la position tirée
		b = new Box(100.f, Vector3D(float(xxx), float(yyy), float(zzz)), Quaternion(1., 0., 0., 0.f), 0.99f, 0.99f, 1.f, 1.f, 1.f);
		//velocite et rotation nulle pour la boite : test en statique
		b->setVelocity(Vector3D(0.f, 0.f, 0.f));
		b->setRotation(Vector3D(0.f, 0.f, 0.f));
		b->setColor(Color::darkGray);
		//on ajoute la primitive associée à la liste + la box à la liste
		primitives_.push_back(new Primitive(b, Bounds(xxx - sizeBox, xxx + sizeBox, yyy - sizeBox, yyy + sizeBox, zzz - sizeBox, zzz + sizeBox)));;
		addBody(b);
		break;

	case 'm'://touche 'm' : broad phase manuelle

		applyCollisions(elapsedTime);

		tree_.display();

		//affiche chaque paire calculée
		for (int k = 0; k < paires_.size(); k++)
		{
			cout << "paire numero " << k ;
			cout << " ("<<(paires_[k].first->bounds_.xmin_ + paires_[k].first->bounds_.xmax_) / 2 << " " << (paires_[k].first->bounds_.ymin_ + paires_[k].first->bounds_.ymax_) / 2 << " " << (paires_[k].first->bounds_.zmin_ + paires_[k].first->bounds_.zmax_) / 2 << ") ";
			cout << "("<<(paires_[k].second->bounds_.xmin_ + paires_[k].second->bounds_.xmax_) / 2 << " " << (paires_[k].second->bounds_.ymin_ + paires_[k].second->bounds_.ymax_) / 2 << " " << (paires_[k].second->bounds_.zmin_ + paires_[k].second->bounds_.zmax_) / 2 <<")"<<endl;
		}
		break;

	case 'v'://touche 'v' : affiche ou non les murs
		break;

	case 'd':
		deleteAndClearAll();
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

//Applique les forces sur les bodies
void Game::applyRegister(float time) {

	std::list<Box*>::iterator it;

	//Register bodies
	for (it = bodies_.begin(); it != bodies_.end(); it++)
	{
		//register_.add(*it, new GravityFG(g_));
	}

	register_.updateForces(time);
	register_.clear();
}

//Applique les mouvements sur les bodies
void Game::applyMovements(float time) {

	std::list<Box*>::iterator it;

	//update physics for each particles
	for (it = bodies_.begin(); it != bodies_.end(); it++)
	{
		//If particle isn't null for some reasons
		if (*it != NULL) {

			//Compute new positions !
			(*it)->integrate(time);

		}
	}

}

//Applique les collisions sur les bodies
void Game::applyCollisions(float time)
{
	//BroadPhase
	//vide l'octree
	tree_.clear();
	//ajoute chaque primitive dans l'octree
	std::list<Primitive*>::iterator it;
	for (it = primitives_.begin(); it != primitives_.end(); it++)
	{
		tree_.insert((*it));
	}
	//vide la liste de paires
	paires_.clear();
	//effectue le pairing
	tree_.pairing(paires_);

	//NarrowPhase
	std::vector<pair<Primitive*, Primitive*>>::iterator itp;
	for (itp = paires_.begin(); itp != paires_.end(); itp++)
	{
		Primitive* a = itp->first;
		Primitive* b = itp->second;
		if (a->hasCollision(b)) {
			cout << "Collision!" << endl;
		}
	}

}

//Dessine les bodies
void Game::drawBodies() {
	std::list<Box*>::iterator it;
	for (it = bodies_.begin(); it != bodies_.end(); it++)
	{
		if (*it != NULL) {
			(*it)->display();
		}
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

	//dessine les bodies
	drawBodies();

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

	applyRegister(elapsedTime);
	applyMovements(elapsedTime);
	applyCollisions(elapsedTime);

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
	cout << "La touche S sert a changer la camera." << endl;
	cout << "La touche B sert a lancer une boite (l'axe change a chaque fois)." << endl;
	cout << "La touche V sert a afficher les murs." << endl;
	cout << "La touche T sert a ajouter un cube avec une position aleatoire dans la zone [-1, 40]." << endl;
	cout << "La touche M sert a lancer une broadphase manuelle." << endl;
	cout << "La touche D sert a supprimer les objets ajoutes par l'utilisateur." << endl;
}

void Game::addBody(Box* rb) {
	bodies_.push_back(rb);
}

void Game::deleteBody(Box* rb) {
	bodies_.remove(rb);
	delete(rb);
}

void Game::deleteAllBodies() {
	while (!bodies_.empty())
		deleteBody(bodies_.front());
}

void Game::deleteAndClearAll() {
	deleteAllBodies();
	register_.clear();
	tree_.clear();
	paires_.clear();
	primitives_.clear();
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