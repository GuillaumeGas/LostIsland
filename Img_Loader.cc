#include "Img_Loader.hh"
#include <fstream>
#include <sstream>
using namespace std;

Img_Loader::Img_Loader(string file) {
    SDL_Surface * surf = NULL;
    surf = SDL_LoadBMP(file.c_str());
    if(!surf) {
	cout << "Erreur !" << endl;
    } else {
	for(int i = 0; i < surf->w; i++) {
	    high_map.push_back(vector<int>());
	    for(int j = 0; j < surf->h; j++) {
		Uint8 r, g, b;
		SDL_GetRGB(((Uint32*)surf->pixels)[i + j * surf->w], surf->format, &r, &g, &b);
		high_map[i].push_back((int)r);
		cout << (int)r << endl;
	    }
	 
	}
    }

  
}

vector<vector<int>> Img_Loader::get_high_map() {
    return high_map;
}
