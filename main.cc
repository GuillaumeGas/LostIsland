#include <GL/glut.h>

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <ctime>

#include "High_Calc.hh"
#include "Img_Loader.hh"

using namespace std;

Img_Loader c( "img.jpg" );
High_Calc h( c.get_high_map() );

int angle = 0;

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
    glEnableClientState(GL_COLOR_ARRAY);
    //glTexCoordPointer(3, GL_FLOAT, 0, h.get_point());
    glColorPointer(3, GL_FLOAT, 0, h.get_color());
    glVertexPointer ( 3, GL_FLOAT, 0, h.get_point() );
    int w = h.get_w();
    for ( int i = 0 ; i < w - 1 ; i++) { 
	glDrawElements( GL_TRIANGLE_STRIP , h.get_w()*2 , GL_UNSIGNED_INT, &h.get_vertex()[w * 2 * i]);
    }

    

}



double dist = -10, hauteur;
int _left = -10, up = 0, front = -50;

void display(void)
{
    framerate();
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //vide r√àellement la fen√çtre
  glLoadIdentity();
  glColor3f(1.0,1.0,1.0);
  gluLookAt(100,100,100,80, -10 ,80,0,1,0);
  glTranslated ( _left,up,front);
  glRotated(angle, 0,1,0);
  dessine();
  glutSwapBuffers();
}



GLubyte CheckImage0[40][40][4];

void makeCheckImage() {
    GLubyte c;
    for(int i = 0 ; i < 40 ; i++ ) {
	for ( int j = 0 ; j < 40 ; j++ ) {
	    c = rand()%255;
	    CheckImage0[i][j][0] = rand()%255;
	    CheckImage0[i][j][1] = rand()%255;
	    CheckImage0[i][j][2] = rand()%255;
	    
	    CheckImage0[i][j][3] = 200;
	}
    }
}


void init (void) 
{
    makeCheckImage();
  glClearColor (0.0, 0.0, 0.0, 0.0); //√àtabli vers quelle couleur la fen√çtre sera vid√àe
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 40,40,0,GL_RGBA, GL_UNSIGNED_BYTE, CheckImage0);
  // glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  // glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
}


void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(70.0, (GLfloat) w/(GLfloat) h, 0.01, 1000.0);
  glMatrixMode(GL_MODELVIEW);

}



void key(unsigned char key,int x,int y) {
  switch ( key ) {
  case 'z':
      front+=2; break;
  case 's':
      front -= 2; break;
  case 'e':
      angle++; break;
  case 'a':
      angle--; break;
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

    case GLUT_KEY_UP: up+=2; break;
    case GLUT_KEY_DOWN: up-=2; break;
	
    case GLUT_KEY_LEFT : _left+=2;printf("Gauche\n ");
      break; 
    case GLUT_KEY_RIGHT : _left-=2; printf("Droite \n");break; 
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
  glutPostRedisplay();
}




int main(int argc, char** argv)
{

    
	
    glutInit(&argc, argv); 

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB  | GLUT_DEPTH ); 
    glutInitWindowSize (500,500);
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
    glutAddSubMenu("Maillages",sMenu);

    glutAttachMenu(GLUT_LEFT_BUTTON);	
	
	

    glutMainLoop();
    return 0;   
}


