#include "Engine.hpp"
#include "Event.hpp"
#include "Img_Loader.hh"
#include "High_Calc.hh"
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "Cube.hpp"
#include "Tree.hpp"
using namespace std;




string framerate() {
 static int frame=0,time,timebase=0;
  static char titre[100];
	
  frame++;
  time = SDL_GetTicks();
  if (time - timebase > 1000) {
      sprintf(titre,"FPS:%4.2f",frame*1000.0/(time-timebase));
      timebase = time;		
      frame = 0;
  }
  return string(titre);
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
    glDisableClientState(GL_COLOR_ARRAY);
}



string load_args(int argc, char ** argv) {
    if ( argc != 1 ) {
	return argv[1];
    } else {
	return "IMG/sauv1.jpg";
    }
}


int main(int argc, char ** argv) {
    srand(time(NULL));
    string img = load_args(argc, argv);
    Img_Loader c(img.c_str());
    int zoom_x = 10.0, zoom_z = 10.0, zoom_y = 1.0;
    High_Calc h(c.get_high_map(), zoom_x, zoom_z, zoom_y);
    int LightPos[] = {h.get_w() * zoom_x,zoom_y * 128 + 100 , h.get_w() * zoom_z,1};
    int MatSpec[] = {0,0,0,0};
    Engine en;
    int largeur = 1000, hauteur = 768;
    en.init("test", largeur, hauteur);
    int _left = -10, up = 0, front = -50;
    en.getCamera()->setLook(100,100,100,80,-10,80,0,1,0); 

    vector<Tree> vec_tree;
    for(int i = 0; i < 400; i++) {
	double x, y, z, he, wi;
	do {
	    x = (double)(rand()%largeur+1);
	    z = (double)(rand()%largeur+1);
	    y = h.get_high(x*zoom_x, z*zoom_z);
	    he = (double)(rand()%150+50);
	} while(y <= 10 || y >= 90);
	vec_tree.push_back(Tree(x, y, z, he, 0.6, 0.6, zoom_x, zoom_y, zoom_z));
    }
    
    Event e;
    int i = 0;
    while (!e[QUIT] ) {
	i++;
	e.UpdateEvent();
	glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,10); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if ( i >  5) {
	    e.setMousePos(largeur/2, hauteur/2);
	    i=0;
	}
	Cube c(0,e.WheelChange() * zoom_y,0,0 ,h.get_w() * h.get_zoom_x(), h.get_w() * h.get_zoom_z());
	en.getCamera()->setLookAt(e(), i);
	en.getCamera()->MovePosition(e, h, c);
	en.getCamera()->look();
	glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
	double x = en.getCamera()->target()._X(), y = en.getCamera()->target()._Y(), z = en.getCamera()->target()._Z();
	dessine(h);
	c.display();
	
	for(auto it : vec_tree) {
	    it.display();
	}

	stringstream fps;
	fps << framerate();
	fps << " X : " << en.getCamera()->position()._X() << " Z :" << en.getCamera()->position()._Z() << " Y : " << en.getCamera()->position()._Y();
	en.change_title(fps.str().c_str());
	SDL_GL_SwapBuffers();


    }
    return 0;
}
