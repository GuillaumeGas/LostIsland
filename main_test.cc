#include "Engine.hpp"
#include "Event.hpp"
#include "Img_Loader.hh"
#include "High_Calc.hh"
#include <iostream>
#include <math.h>
using namespace std;


Img_Loader c("img.jpg");
High_Calc h(c.get_high_map());



void dessine() {
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
    Engine en;
    int w = 1000, h = 768;
    en.init("test", w, h);
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
	    e.setMousePos(w/2, h/2);
	    i=0;
	}
	en.getCamera()->setLookAt(e(), i);
	en.getCamera()->MovePosition(e);
	en.getCamera()->look();
	glTranslated(_left,up, front);
	dessine();
	SDL_GL_SwapBuffers();


    }
    return 0;
}
