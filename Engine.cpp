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
  glClearColor( 0.0,0.0,0.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)640/480, 1, 1000);
  glEnable(GL_DEPTH_TEST);
}

void Engine::change_title(string titre) {
    SDL_WM_SetCaption(titre.c_str(), NULL);
}


Camera * Engine::getCamera() {
  return &m_cam;
}
