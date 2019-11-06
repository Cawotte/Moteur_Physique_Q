#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>     
#include <time.h>

#include "Game.h"
#include "Quaternion.h"
#include <math.h>

void static testQuaternion();

int main(int argc, char** argv) {

	testQuaternion();

	Game jeu;
	//jeu.execute(argc, argv);

	int val;
	cin >> val;

	return 0;
}

void static testQuaternion() {

	float pi = atan(1) * 4;

	//Product
	Quaternion q{ 0.5f, 0.5f, 0.5f, 0.5f };

	Quaternion q2{ 0.f, 0.f, pi, 0.f };

	Quaternion product = q2 * q;

	cout << "product:" << endl;
	product.print();
	cout << endl << endl;

	//Angular velocity
	Vector3D theta{ 0.f, pi, 0.f };
	q.updateAngularVelocity(theta, 2.f);


	cout << "angular velocity:" << endl;
	q.print();
	cout << endl << endl;

}