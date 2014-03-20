#ifndef DEF_INPUT
#define DEF_INPUT

#include <SDL/SDL.h>

struct Input{
  char m_key[SDLK_LAST];
  int m_mouse_x, m_mouse_y;
  int m_mouse_xrel, m_mouse_yrel;
  char m_mousebuttons[8];
};


enum Mapp{
    LEFT, RIGHT, UP, DOWN,SHIFT,  QUIT , MAP_INTER, LEFT_CL , RIGHT_CL,  MAP_LAST
};

struct position_t{
  int m_x, m_y;
};


class Event {
public: 

    Event();

    void change_key(Mapp m, SDLKey k);
    void UpdateEvent();
    bool key_pressed(Mapp m);
    void reset_pressed(Mapp m);
    int & WheelChange();//renvoi un chiffre positif si la molette est vers le haut et negatif si elle est vers le bas (le int est le nombre de tour) et 0 si il n'y as aucun changement
    void setMousePos(int x, int y);    
    SDL_Event & getEvent();
    char& operator[](Mapp m);
    position_t operator()();
    



private:
    Input m_in;
    SDLKey m_mapping[MAP_INTER];
    int m_mouse_mapping[MAP_LAST];
    SDL_Event m_event;
    int m_wheel;
    int m_sensivity;
  
};


#endif
