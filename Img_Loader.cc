#include "Img_Loader.hh"
#include <fstream>
#include <sstream>
using namespace std;


Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
    switch(nbOctetsParPixel)
	{
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
        default:
            return 0; 
	}
}


Img_Loader::Img_Loader(string file) {
    SDL_Surface * surf = NULL;
    surf = IMG_Load(file.c_str());
    if(!surf) {
	cout << "Erreur !" << endl;
    } else {
	for(int i = 0; i < surf->w ; i++ ) {
	    for ( int j = 0  ; j < surf->h ; j++) {
		Uint32 pixel = obtenirPixel(surf, i, j);
		Uint8 r, g, b, a;
		SDL_GetRGBA(pixel, surf->format, &r, &g, &b, &a);
		high_map.push_back((int)r);

	    }
	}
    }
}

vector<int> Img_Loader::get_high_map() {
    return high_map;
}
