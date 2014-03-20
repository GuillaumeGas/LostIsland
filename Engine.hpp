#ifndef DEF_ENGINE
#define DEF_ENGINE

/**
   Moteur 3d de fifou
 */

/* temporaire, fodrai passer à la sdl */
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <vector>
#include "Camera.hpp"
#include "Event.hpp"

class Engine {
  
public:
  Engine();
  ~Engine();
  
  void init(char* titre, int w, int h);

  Camera * getCamera();


private:
  SDL_Event m_event;
  Camera m_cam;
};

#endif
