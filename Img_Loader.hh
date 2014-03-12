#ifndef _LOAD_IMG
#define _LAOD_IMG


#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Img_Loader {
public:
    
    Img_Loader ( std::string file );

private:

    std::vector < std::vector < int > > high_map;

};



#endif
