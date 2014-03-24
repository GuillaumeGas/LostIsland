#include "Engine.hpp"
using namespace std;

Engine::Engine() {}

Engine::~Engine() {

}

void Engine::init(string titre, int w, int h) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption(titre.c_str(), NULL);
  SDL_SetVideoMode(w, h, 32, SDL_OPENGL);
  SDL_WM_GrabInput(SDL_GRAB_ON);
  SDL_ShowCursor(SDL_DISABLE);
  glClearColor( 0.5,0.5,0.5,1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)h/w, 1, 100000);
  //glEnable(GL_FOG) ;
  GLfloat fogcolor[4] = {0.5, 0.5, 0.5, 1} ;
  GLint fogmode = GL_EXP ;
  glFogi (GL_FOG_MODE, fogmode) ;
  glFogfv(GL_FOG_COLOR, fogcolor) ;
  glFogf(GL_FOG_DENSITY, 0.005) ;
  glFogf(GL_FOG_START, 1.0) ;
  glFogf(GL_FOG_END, 5.0) ;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
}

void Engine::change_title(string titre) {
    SDL_WM_SetCaption(titre.c_str(), NULL);
}


Camera * Engine::getCamera() {
  return &m_cam;
}
