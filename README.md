# Systeme-Solaire
Simulation du systeme solaire - C++ - OpenGel

### Photos du système solaire fini

![](https://github.com/crambille/Systeme-Solaire/blob/master/resultat/s3.png)


![](https://github.com/crambille/Systeme-Solaire/blob/master/resultat/s4.png)

![](https://github.com/crambille/Systeme-Solaire/blob/master/resultat/s5.bmp)

![](https://github.com/crambille/Systeme-Solaire/blob/master/resultat/s6.bmp)


Réalisation d'un mini système solaire
Pour simplifier la réalisation on ne concidère qu'une représentation partielle du système solaire :
-	le soleil
-	mercure
-	vénus
-	la terre
-	et la lune.

Dimensions des planètes (''proportionnelles'' aux tailles réelles):

* Soleil : 109
* Mercure :8.8
* Vénus : 14.4
* La Terre : 15
* La Lune : 4
* Mars : 10.32
.

Toutes ces planètes seront sur le même plan, et graviteront autour du soleil, la lune gravitant elle autour de la terre. 
Déterminer les orbites (primitives OpenGL) pour avoir un rendu ''réaliste''

Le travail à réaliser se décomposer en quatres parties :
* Mise en place des objets planètes(le soleil, mercure, vénus, la terre et la lune) et de leurs orbites.
* Réaliser l'animation en choisissant l'une techniques disponibles avec OpenGL (ProjetAnimation).
* Coder pour l'interface clavier les touches suivantes:
* Ajout des textures

### Commandes:
* ‘r’ : Lance/Arrête de l’animation ‘-’ : Zoom arrière.
* ‘+’ : Zoom avant.
* 'o' : Cacher les orbites
* 'O' : Afficher les orbites
* 'x' : rotation/axe des x 'y' rotation/axe des y 'z' rotation/axe des z
* 'X' : translation suivant l'axe des x 'Y' translation suivant l'axe des y 'Y' translation suivant l'axe des z 
* 'l' : affiche la scène avec une caméra embarquée sur la lune orientée vers la terre.
* 'L' : affiche la scène avec une caméra exterieur afin de voir tout le système solaire.
