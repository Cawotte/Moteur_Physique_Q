#### Téléchargement

* **Glew (2.1.0)** : http://glew.sourceforge.net/

* **FreeGlut (3.0.0)** : https://www.transmissionzero.co.uk/software/freeglut-devel/

#### Dans Visual Studio
**1.** Ouvrir le projet cloné

**2.** Projet -> Propriétés de Moteur_physiqueC/C++ -> Général -> Autres répertoires Include -> \<Modifier> -> Ajouter les répertoires include pour freeglut et glew 
* Exemple :
	* D:\Programmes\freeglut\include
	* D:\Programmes\GLEW-2.1.0\glew-2.1.0\include

**3.** Editeur de liens -> Général -> Répertoires de bibliothèques supplémentaires -> \<Modifier> -> Ajouter les répertoires qui contiennent les .lib pour freeglut et glew
* Exemple : 
	* D:\Programmes\freeglut\lib\x64
	* D:\Programmes\GLEW-2.1.0\glew-2.1.0\lib\Release\x64

**4.** Editeur de liens -> entrée -> Dépendances supplémentaires -> \<Modifier> -> Ajouter glew32.lib freeglut.lib opengl32.lib

***

Si ça indique quand vous éxecutez qu'il manque des dll, copiez freeglut.dll et glew.dll à côté de l'exécutable dans le dossier Debug.
Les .dll sont dans le dossier bin ou lib des dossiers dézippés.
