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
#include <iostream>

class Engine {
  
public:
  Engine();
  ~Engine();
  
    void init(std::string titre, int w, int h);
    void change_title(std::string);
    
    Camera * getCamera();
    SDL_Surface * get_ecran();

private:
    SDL_Event m_event;
    SDL_Surface * ecran;
    Camera m_cam;
};

#endif
