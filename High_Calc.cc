#include "High_Calc.hh"
#include <iostream>
using namespace std;

High_Calc::High_Calc ( vector <int> v ) {
    W = sqrt(v.size());
    vert = new int[W * 2 * W];
    point = new float[ W * W * 3];
    for ( auto it : v ) {
	height.push_back ( (it - 128) );
    }
    genere_point();
    genere_vertex();
}


void High_Calc::genere_point ( ) {
    int c = 0;
    for ( int j = 0 ; j < W ; j++ ) {
	for ( int i = 0 ; i < W ; i ++ ) {
	    point [ c ] = j;
	    point [ c + 2 ] = i;
	    point [ c + 1 ] = height[i + j * W];
	    c += 3;

	}
    }
}


int High_Calc::get_w() {
    return W;
}


void High_Calc::genere_vertex ( ) {
    int c = 0;
    for ( int i = 0 ; i < W ; i++) {
	for ( int j = 0 ; j < W ; j++ ) {
	    vert[c] = j + i * W;
	    vert[c+1] = j + W + i * W;
	    c+=2;
	}
    }
}


int * High_Calc::get_vertex ( ) {
    return vert;
}


float * High_Calc::get_point ( ) {
    return point;
}


int High_Calc::get_size ( ) {
    return size;
}
