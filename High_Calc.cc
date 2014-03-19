#include "High_Calc.hh"
#include <iostream>
using namespace std;

High_Calc::High_Calc ( vector < vector < int > > v ) {
    int i = 0;
    point = new float[ (v.size() * v[0].size()) * 3];
    size = (v.size() * v[0].size()) * 3;
    cout << size << endl;
    vert = new int [ size/3 ];
    
    for ( auto it : v ) {
	height.push_back ( vector < int >() );
	for ( auto it2 : it ) {
	    height[i].push_back ( (it2 - 128) / 10.0 );
	}
	i++;
    }
    genere_point();
    genere_vertex();
}


void High_Calc::genere_point ( ) {
    int c = 0;
    for ( int i = 0 ; i < height.size() ; i ++ ) {
	for ( int j = 0 ; j < height.size(); j ++ ) {
	    point [ c ] = j;
	    point [ c + 1 ] = height[i][j]/10.0;
	    point [ c + 2 ] = i;
	    c += 3;
	}
    }
}


void High_Calc::genere_vertex ( ) {
    for (int i = 0 ; i < size/3 ; i++ ) {
	vert[i] = i;
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
