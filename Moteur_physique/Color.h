
#ifndef COLOR
#define COLOR

#include "Vector3D.h"

/* Color : permet d'acc�der facilement aux couleurs utilitaires.
Chaque membre, soit chaque couleur, correspond � un Vector3D, soit les composantes RGB de la couleur en question.
*/
class Color
{
public:
	static Vector3D red;
	static Vector3D blue;
	static Vector3D green;

	static Vector3D white;
	static Vector3D black;

	static Vector3D yellow;
	static Vector3D orange;
	static Vector3D cyan;
	static Vector3D purple;
	static Vector3D gray;

	static Vector3D lightGray;
	static Vector3D darkGray;

	static Vector3D brown;
	static Vector3D lightBlue;

};
#endif