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
#include "ObjectOff.hpp"

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




void load(vector<float> &somm, vector<int> & ind, const char * file ) {
   ifstream f(file, ios::in);
    string ch;
    int aux;
    int nbSommets, nbIndex;
    
    f >> ch >> nbSommets >> nbIndex >> aux;

    if(ch == "OFF") {
	int j = 0;
	for(int i = 0; i < nbSommets; i++) {
	    float a,b,c;
	    f >> a >> b >> c;
	    somm.push_back(a);
	    somm.push_back(b);
	    somm.push_back(c);
	}
	
	int nb;
	f >> nb;
	j = 0;
	for(int i = 0; i < nbIndex; i++) {
	    for(int k = 0; k < nb; k++) {
		int a;
		f >> a;
		ind.push_back(a);
	    }
	    f >> nb;
	}
    } else {
	cout << "Erreur, fichier inconnu." << endl;
	throw -1;
    }
    f.close();
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

    int MatSpec[] = {0,0,0,0};
    Engine en;
    int largeur = 1000, hauteur = 768;
    en.init("test", largeur, hauteur);
    int _left = -10, up = 0, front = -50;
    en.getCamera()->setLook(0,100,100,80,-10,80,0,1,0); 

    vector <float> position;
    for ( int i = 0 ; i < 1 * 3 ; i+=3 ) {
	double x, y, z;
	do {
	    x = (double)(rand()%h.get_w()*zoom_x+1);
	    z = (double)(rand()%h.get_w()*zoom_z+1);
	    y = h.get_high(x, z) + 5;
	} while(y <= 10 || y >= 90);
	position.push_back(x);
	position.push_back(y);
	position.push_back(z);

    }


    vector<Tree> vec_tree;
    for(int i = 0; i < 400; i++) {
	double x, y, z, he, wi;
	do {
	    x = (double)(rand()%h.get_w() + 1);
	    z = (double)(rand()%h.get_w() + 1);
	    y = h.get_high(x * zoom_x, z * zoom_z) - 5;
	    he = (double)(rand()%150+50);
	} while(y <= 10 || y >= 90);
	vec_tree.push_back(Tree(x, y, z, he, 0.6, 0.6, zoom_x, zoom_y, zoom_z));
    }
    
    ObjectOff obsf("maillages/triceratops.off");

    Event e;
    int i = 0;
    GLfloat dif[] = {0.0,0.0,0.0,1.0};
    bool retour = false;
    int LightPos[] = {0,100 , 0,1};
    bool retour_lum = false;
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
	if ( e[LEFT_CL] ) {
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(20, (double)hauteur/largeur, 1, 100000);
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	} else {
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(70, (double)hauteur/largeur, 1, 100000);
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	    
	}

	Cube c(0,e.WheelChange() * zoom_y,0,0 ,h.get_w() * h.get_zoom_x(), h.get_w() * h.get_zoom_z());
	Cube c2(LightPos[0], LightPos[1], LightPos[2], 10,10,10);
	en.getCamera()->setLookAt(e(), i);
	en.getCamera()->MovePosition(e, h, c);
	en.getCamera()->look();

	glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,dif); 

	double x = en.getCamera()->target()._X(), y = en.getCamera()->target()._Y(), z = en.getCamera()->target()._Z();

	
	dessine(h);

	
	for(auto it : vec_tree) {
	    it.display();
	}

	for ( int i = 0 ; i < position.size() ; i+=3 ) {
	    glColor3d(1.0,1.0,1.0);
	    obsf.set_pos(position[i], position[i+1], position[i+2]);

	    obsf.display();
	}
	


	if ( retour_lum ) {
	    if ( LightPos[0] > 0 ) {
		LightPos[0] -= 100;
		LightPos[2]-= 100; 
	    } else {
		retour_lum = false;
	    }
	} else {
	    if ( LightPos[0] < h.get_w() * zoom_x ) {
		LightPos[0] += 100;
		LightPos[2] += 100;
	    } else {
		retour_lum = true;
	    }
	}




	if ( retour ) {
	    if ( dif[1] > 0.0f ){
		dif[1] -= 0.05f;
		dif[2] -= 0.05f;
	    } else if ( dif[0] > 0.0f ) {
		dif[0] -= 0.01f;
	    } else {
		retour = false;
	    } 
	} else {
	    if ( dif[0] < 0.7f ) {
		dif[0] += 0.01f;
		dif[1] += 0.01f;
		dif[2] += 0.01f;
	    } else {
		retour = true;
	    }
	}
	c.display();
	c2.display();
	stringstream fps;
	fps << framerate();
	fps << " X : " << en.getCamera()->position()._X() << " Z :" << en.getCamera()->position()._Z() << " Y : " << en.getCamera()->position()._Y();
	en.change_title(fps.str().c_str());
	SDL_GL_SwapBuffers();


    }
    return 0;
}
