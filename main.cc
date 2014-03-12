#include <GL/glut.h>

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <ctime>

using namespace std;




void MyReDisplay(void)
{
  glutPostRedisplay();

}



void framerate(void){
  static int frame=0,time,timebase=0;
  static char titre[100];
	
  frame++;
  time=glutGet(GLUT_ELAPSED_TIME);
  if (time - timebase > 1000) {
    sprintf(titre,"FPS:%4.2f",
	    frame*1000.0/(time-timebase));
    glutSetWindowTitle(titre);	
    timebase = time;		
    frame = 0;
  }
	
}	



void dessine() {
    glColor3d(1,1,1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(3, GL_FLOAT, 0, somm);
    glVertexPointer(3, GL_FLOAT, 0, somm);
    /* glDrawElements(GL_TRIANGLES, 6*3, GL_UNSIGNED_INT, pignons);
    glColor3d(1,0,1);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, toit);
    glColor3d(1,1,0);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, murs);*/
    glDrawElements(GL_TRIANGLES, nb_int*3, GL_UNSIGNED_INT, index_);

}



double dist = -10, hauteur;

void display(void)
{
    framerate();
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //vide r√àellement la fen√çtre
  glLoadIdentity();
  glColor3d(1,1,0);
  glTranslated(0,hauteur,0);
  glTranslated(0,0,dist);
    glRotated(angle, 0,1,0);
    //glRotated(angle, 1,0,0);
  dessine();
  glutSwapBuffers();
}


void init (void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0); //√àtabli vers quelle couleur la fen√çtre sera vid√àe
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
}


void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(70.0, (GLfloat) w/(GLfloat) h, 0.01, 100.0);
  glMatrixMode(GL_MODELVIEW);

}



void key(unsigned char key,int x,int y) {
  switch ( key ) {
  case 'w'  : R-=0.1f;printf(" %f -Rayon \n",R);						
    break;
  case 'x'  : R+=0.1f; printf(" %f +Rayon \n",R);			       
    break;			
  case 'z' : hauteur -= 0.1; break;
  case 's' : hauteur -= 0.1; break;
  case 0x1B : exit(0); }
  MyReDisplay();
}

void GestionSpecial(int key, int x, int y)
{printf("vous avez appuy√à sur ");
  switch (key)
    {	
    case GLUT_KEY_F1 : printf("F1 \n");glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      
      break;
    case GLUT_KEY_F2 : printf("F2 \n");glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);break;

    case GLUT_KEY_UP: dist+=0.1; break;
    case GLUT_KEY_DOWN: dist-=0.1; break;
	
    case GLUT_KEY_LEFT : hauteur+=2;printf("Gauche\n ");
      break; 
    case GLUT_KEY_RIGHT : hauteur-=2; printf("Droite \n");break; 
    }	
  printf("position de la souris : ");
  printf("%d,%d ",x,y);
  MyReDisplay();
	
}	

void Effets(int selection)
{ 
	
  switch (selection)
    {	
    case 0 : 	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);break; 
    case 1 :glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);break; 
    case 2 :exit(0);break; 
    }		
	
  MyReDisplay();	
}

void Menu2(int selection)
{ 
  printf("selection Menu2 %i",selection);
  switch (selection)
    {	
    case 0 : 	printf("action toto");break; 
    case 1:	printf("action titi");break; 	
    }	
  MyReDisplay();	
}

void spinDisplay(void)
{
    angle++;
  glutPostRedisplay();
}




int main(int argc, char** argv)
{
	
  glutInit(&argc, argv); 

  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB  | GLUT_DEPTH ); 
  glutInitWindowSize (50,50);
  glutInitWindowPosition (100, 350);
  glutCreateWindow ("Second Window"); 
  init ();
  glutReshapeFunc(reshape);
  glutKeyboardFunc(key);
  glutSpecialFunc(GestionSpecial);
  glutDisplayFunc(display); 
  glutIdleFunc(spinDisplay);

	
  int sMenu;
  sMenu = glutCreateMenu(Menu2);
  glutAddMenuEntry("toto",0);
  glutAddMenuEntry("titi",1);

  int mainMenu;
  mainMenu = glutCreateMenu(Effets);
  glutAddMenuEntry("Mode plein",0);
  glutAddMenuEntry("Mode fil de fer",1);
  glutAddMenuEntry("Quitter",2);
  glutAddSubMenu("Maillages",
		 sMenu);

  glutAttachMenu(GLUT_LEFT_BUTTON);	
	
	

  glutMainLoop();
  return 0;   
}


