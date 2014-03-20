#include "Engine.hpp"

Engine::Engine() {}

Engine::~Engine() {

}

void Engine::init(char* titre, int w, int h) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption(titre, NULL);
  SDL_SetVideoMode(w, h, 32, SDL_OPENGL);
  SDL_WM_GrabInput(SDL_GRAB_ON);
  SDL_ShowCursor(SDL_DISABLE);
  glClearColor( 0.0,0.0,0.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)640/480, 1, 1000);
  glEnable(GL_DEPTH_TEST);
}




Camera * Engine::getCamera() {
  return &m_cam;
}
