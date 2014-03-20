#include "Engine.hpp"
#include "Event.hpp"
#include "Img_Loader.hh"
#include "High_Calc.hh"
#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;




void framerate(Engine & e) {
 static int frame=0,time,timebase=0;
  static char titre[100];
	
  frame++;
  time = SDL_GetTicks();
  if (time - timebase > 1000) {
      sprintf(titre,"FPS:%4.2f",
	      frame*1000.0/(time-timebase));
      e.change_title(titre);
      timebase = time;		
      frame = 0;
  }  
}


void dessine(High_Calc & h) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, h.get_color());
    glVertexPointer ( 3, GL_FLOAT, 0, h.get_point() );
    int w = h.get_w();
    for ( int i = 0 ; i < w - 1 ; i++) {
	glDrawElements( GL_TRIANGLE_STRIP , h.get_w()*2 , GL_UNSIGNED_INT, &h.get_vertex()[w * 2 * i]);
    }    
}


int main(int argc, char ** argv) {
    Img_Loader c(argv[1]);
    High_Calc h(c.get_high_map());
    Engine en;
    int largeur = 1000, hauteur = 768;
    en.init("test", largeur, hauteur);
    int _left = -10, up = 0, front = -50;
en.getCamera()->setLook(100,100,100,80,-10,80,0,1,0); 

    Event e;
    int i = 0;
    while (!e[QUIT] ) {
	i++;
	e.UpdateEvent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if ( i >  5) {
	    e.setMousePos(largeur/2, hauteur/2);
	    i=0;
	}
	en.getCamera()->setLookAt(e(), i);
	en.getCamera()->MovePosition(e);
	en.getCamera()->look();
	glTranslated(_left,up, front);
	dessine(h);
	framerate(en);
	SDL_GL_SwapBuffers();


    }
    return 0;
}
