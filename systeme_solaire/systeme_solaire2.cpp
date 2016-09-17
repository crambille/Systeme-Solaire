/*****************************************
IMERIR
Infographie 1

*******************************************/  

#include <stdio.h> 
#include <windows.h>
#include <stdlib.h>     
#include <math.h>
#include <iostream>

#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>

#define WIDTH  960
#define HEIGHT 960

#define RED   1
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define KEY_ESC 27

int angle1 = 1;
int angle2 = 1;
int r = 400;
float pi = 3.14;
int transx = 0;
int transy = 0;
int transz = 0;
int r_mercure = 0;
int r_venus = 0;
int r_terre = 0;
int r_mars = 0;
int r_lune = 0;
int cacher = 0;
int pause = 0;
int rx = 0;
int ry = 0;
int rz = 0;
int camera = 0;

//GLUquadricObj *obj = gluNewQuadric();

//LoadBMP : charge une image 24bpp
#define EXIT {fclose(fichier);return -1;}
#define CTOI(C) (*(int*)&C)	//récupère en int un nombre pointé par un char*

int LoadBMP(char *File);
void init_scene();
GLvoid initGL();
void Init_light();
void rotation_planete();
void dessiner_cercle(rayon_cercle);
GLvoid mon_window_display();
void mon_window_key(unsigned char key, int x, int y);
GLvoid mon_window_reshape(GLsizei width, GLsizei height); 
GLvoid mon_window_key(unsigned char key, int x, int y); 

int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  // initialisation du contexte grapique
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  // définition et création de la fenêtre graphique
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carré");

  // initialisation de OpenGL et de la scène
  initGL();  
  Init_light();
  
  // choix des procédures de callback pour 
  // le tracé graphique
  glutDisplayFunc(&mon_window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&mon_window_reshape);
  // la gestion des événements clavier
  glutKeyboardFunc(&mon_window_key);

  // la boucle prinicipale de gestion des événements utilisateur
  
  //Rotation des planètes
  glutTimerFunc(3, rotation_planete, 0);

  glutMainLoop();  
  

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL() 
{
  glClearColor(0,0,0,1);  //ALPHA      
  glClear(GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
}


// fonction de call-back pour l´affichage dans la fenêtre

GLvoid mon_window_display()
{
 
  glClear(GL_DEPTH_BUFFER_BIT); // initialise le buffer à la couleur du fond. 
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();		//initialisation de la matrice courant GL_MODELVIEW 

  //Integration d'une caméra

  //par rapport a lorginie 
  if (camera == 0)
	gluLookAt(transx + r*cos(angle2*pi / 180)*sin(angle1*pi / 180), transy + r*sin(angle2*pi / 180)*sin(angle1*pi / 180),transz +  r*cos(angle1*pi / 180), transx, transy, transz, 0, 1, 0);
  
  //Affichage des axes
  glBegin(GL_LINES);
  glColor3f(1,0,0); // axe jaune x
  glVertex3f(400, 0, 0);
  glVertex3f(0, 0, 0);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(0, 1, 0); // axe vert y 
  glVertex3f(0, 0, 0);
  glVertex3f(0, 400, 0);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(1, 1, 1); // axe blanc z
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 400);
  glEnd();


  glEnable(GL_DEPTH_TEST);
  //glDisable(GL_DEPTH_TEST);

  glEnable(GL_LIGHTING); // Active la gestion des lumières
  glEnable(GL_LIGHT0);

  //ROTATION
  glRotatef(rx, 1, 0, 0);
  glRotatef(ry, 0, 1, 0);
  glRotatef(rz, 0, 0, 1);

  //Soleil
  glColor3f(1, 1, 0); // jaune
  glPushMatrix();
  glutSolidSphere(109, 50, 50);
  glPopMatrix();
  
  
  //mercure
  glPushMatrix();
  glColor3f(1, 0, 0); // rouge
  if (cacher == 0)
	  dessiner_cercle(150);
  glRotatef(r_mercure, 0, 1, 0);
  glTranslatef(150, 0, 0);
  glutSolidSphere(8.8, 50, 50);
  glPopMatrix();
  
  //venus
  glPushMatrix();
  glColor3f(0, 1, 0); // vert
  if (cacher == 0)
	dessiner_cercle(200);
  glRotatef(r_venus, 0, 1, 0);
  glTranslatef(200, 0, 0);
  glutSolidSphere(14.4, 50, 50);
  glPopMatrix();

  //la terre
  glPushMatrix();
  glColor3f(0, 0, 1); // bleu
  if (cacher == 0)
	dessiner_cercle(250);
  glRotatef(r_terre, 0, 1, 0);
  glTranslatef(250, 0, 0);
  glutSolidSphere(15, 50, 50);


  //la lune
  glColor3f(1, 1, 1); // blanc
  if (cacher == 0)
	dessiner_cercle(25);
  glRotatef(r_lune, 0, 1, 0);
  glTranslatef(25, 0, 0);
  glutSolidSphere(4, 50, 50);
  if (camera == 1)
	  gluLookAt(500 + cos(angle2*pi / 180)*sin(angle1*pi / 180), 500 + sin(angle2*pi / 180)*sin(angle1*pi / 180), 500 + cos(angle1*pi / 180), 500, 500, 500, 0, 1, 0);

  glPopMatrix();

  //Mars
  glPushMatrix();
  glColor3f(0, 1, 1); // violet
  if (cacher == 0)
	dessiner_cercle(350);
  glRotatef(r_mars, 0, 1, 0);
  glTranslatef(350, 0, 0);
  glutSolidSphere(10.32, 50, 50);
  glPopMatrix();

  // trace la scène grapnique stocké dans le buffer image qui vient juste d'être définie
  glFlush();
  glutSwapBuffers();
}

// fonction de call-back pour le redimensionnement de la fenêtre si on modifie sa taile.

GLvoid mon_window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height); 

  glMatrixMode(GL_PROJECTION); //indique le type  de transformation et charge la matrice correspondante 
  glLoadIdentity();		//Initialise la matrice courante à la matrice Identité.
  gluPerspective(90, 1, 1, 1000);//définit le type de projection : orthogonal 2D,
  //et ses paramètres à partir desquels OpenGl construit la matrice de projection correspondante.

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier
GLvoid mon_window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break; 

  case '-': //DEZOOM
	  r = r *2;
	  glutPostRedisplay();           
	  break;

  case '+': //ZOOM
	  r = r /2;
	  glutPostRedisplay();           
	  break;

  case 'x':	//ROTATION DE X
	  rx = rx + 10;
	  glutPostRedisplay();
	  break;

  case 'y': //ROTATION DE Y
	  ry = ry + 10;
	  glutPostRedisplay();
	  break;

  case 'z': // ROTATION DE Z
	  rz = rz + 10;
	  glutPostRedisplay();
	  break;

  case 'X':	//DEPLACEMENT DE X
	  transx = transx + 10;
	  glutPostRedisplay();           
	  break;

  case 'Y': //DEPLACEMENT DE Y
	  transy = transy + 10;
	  glutPostRedisplay();           
	  break;

  case 'Z': // DEPLACEMENT DE Z
	  transz = transz + 10;
	  glutPostRedisplay();            
	  break;

  case 'o': // CACHER OU PAS ORBITE
	  cacher = 1;
	  glutPostRedisplay();          
	  break;

  case 'O': // CACHER OU PAS ORBITE
	  cacher = 0;
	  glutPostRedisplay();
	  break;

  case 'r': // METTRE SUR PAUSE
	  pause = 1;
	  glutPostRedisplay();
	  break;

  case 'R': // RELANCER
	  pause = 0;
	  rotation_planete();
	  glutPostRedisplay();
	  break;

  case 'l': // CAMERA SUR LA LUNE
	  camera = 1;
	  glutPostRedisplay();
	  break;

  case 'L': // CAMERA SUR LA LUNE
	  camera = 0;
	  glutPostRedisplay();
	  break;


  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }     
}

void Init_light()
{
	//différents paramètres
	GLfloat ambient[] = { 0.15f, 0.15f, 0.15f, 1.0f };
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat light0_position[] = { 0.0f, -10.0f, 0.0f, 0.0f };
	GLfloat specular_reflexion[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLubyte shiny_obj = 128;
	//positionnement de la lumière avec les différents paramètres
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHT0);
	//spécification de la réflexion sur les matériaux
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_reflexion);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shiny_obj);
}

void rotation_planete()
{
	if (pause == 0)
	{
		r_mercure = r_mercure + 3.3;
		r_venus = r_venus + 2.4;
		r_terre = r_terre + 2;
		r_mars = r_mars + 1.6;
		r_lune = r_lune + 5;
		mon_window_display();
		glutTimerFunc(50, rotation_planete, 0);
	}

}


void dessiner_cercle(rayon_cercle)
{
	float i;
	glBegin(GL_LINE_LOOP); 
	
	for (i = 0; i < 2*pi; i+=pi/100)
	{
		glVertex3f(rayon_cercle*cos(i), 0, rayon_cercle*sin(i));
	}
	glEnd();
}

int LoadBMP(char *File)
{
	unsigned char	*Data;
	FILE			*fichier;
	unsigned char	Header[0x36];
	GLuint			DataPos, DataSize;
	GLint			Components;
	GLsizei			Width, Height;
	GLenum			Format, Type;
	GLuint			Name[1];

	//Lit le fichier et son header
	fichier = fopen(File, "rb"); if (!fichier) return -1;
	if (fread(Header, 1, 0x36, fichier) != 0x36) EXIT;
	if (Header[0] != 'B' || Header[1] != 'M')	EXIT;
	if (CTOI(Header[0x1E]) != 0)				EXIT;
	if (CTOI(Header[0x1C]) != 24)				EXIT;

	//Récupère les infos du fichier
	DataPos = CTOI(Header[0x0A]);
	DataSize = CTOI(Header[0x22]);
	//Récupère les infos de l'image
	Width = CTOI(Header[0x12]);
	Height = CTOI(Header[0x16]);
	Type = GL_UNSIGNED_BYTE;
	Format = GL_RGB;
	Components = 3;

	//!!!!
	if (DataSize == 0) DataSize = Width*Height*Components;
	if (DataPos == 0)  DataPos = 0x36;

	//Charge l'image
	fseek(fichier, DataPos, 0);
	Data = new unsigned char[DataSize];
	if (!Data) EXIT;

	if (fread(Data, 1, DataSize, fichier) != DataSize)
	{
		delete Data;
		fclose(fichier);
		return -1;
	}

	fclose(fichier);

	//Inverse R et B
	unsigned char t;
	for (int x = 0; x<Width*Height; x++)
	{
		t = Data[x * 3];
		Data[x * 3] = Data[x * 3 + 2];
		Data[x * 3 + 2] = t;
	}

	//Envoie la texture à OpenGL
	//	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1, Name);
	glBindTexture(GL_TEXTURE_2D, Name[0]);


	glTexImage2D
		(
		GL_TEXTURE_2D, 	//target
		0,				//mipmap level
		Components,		//nb couleurs
		Width,			//largeur
		Height,			//hauteur
		0,			 	//largeur du bord
		GL_RGB,			//type des couleurs
		GL_UNSIGNED_BYTE,			//codage de chaque composante
		Data			//Image
		);

	return Name[0];
}

