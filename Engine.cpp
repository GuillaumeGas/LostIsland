#include "Engine.hpp"
using namespace std;

Engine::Engine() {}

Engine::~Engine() {

}

void Engine::init(string titre, int w, int h) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption(titre.c_str(), NULL);
  ecran = SDL_SetVideoMode(w, h, 32, SDL_OPENGL);
  SDL_WM_GrabInput(SDL_GRAB_ON);
  SDL_ShowCursor(SDL_DISABLE);
  glClearColor( 0.5,0.5,0.5,1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)h/w, 1, 100000);
  glEnable(GL_FOG) ;
  GLfloat fogcolor[4] = {0.5, 0.5, 0.5, 1} ;
  GLint fogmode = GL_EXP ;
  glFogi (GL_FOG_MODE, fogmode) ;
  glFogfv(GL_FOG_COLOR, fogcolor) ;
  glFogf(GL_FOG_DENSITY, 0.001) ;
  glFogf(GL_FOG_START, 1.0) ;
  glFogf(GL_FOG_END, 5.0) ;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat dif[] = {0.0,0.0,0.0,1.0}; 
  glLightfv(GL_LIGHT0,GL_DIFFUSE,dif); 
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LESS);
}

void Engine::change_title(string titre) {
    SDL_WM_SetCaption(titre.c_str(), NULL);
}


Camera * Engine::getCamera() {
  return &m_cam;
}


SDL_Surface * Engine::get_ecran() {
    return ecran;
}
