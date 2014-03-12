#include "High_Calc.hh"
using namespace std;

High_Calc::High_Calc ( vector < vector < int > > v ) {
    int i = 0;
    point = new float[ (v.size() * v[0].size()) * 3 ];
    int size = (v.size() * v[0].size()) * 3;
    vert = new int [ size/3 ];
    
    for ( auto it : v ) {
	height.push_back ( vector < int >() );
	for ( auto it2 : it ) {
	    
	    height[i].push_back ( ( ( - it2 ) + 128 ) );
	}
    }
}


void High_Calc::genere_point ( ) {
    int c = 0;
    for ( int i = 0 ; i < height.size() ; i ++ ) {
	for ( int j = 0 ; j < height[i].size() ; j ++ ) {
	    point [ c ] = (float)(j/height.size()*1.0);
	    point [ c + 1 ] = (float)(height[i][j]*1.0);
	    point [ c + 2 ] = (float)(i/height[i].size()*1.0);
	    c += 3;
	}
    }
}


void High_Calc::genere_vertex ( ) {
    
    for ( int i = 0 ; i < size/3 ; i++ ) {
	vert[i] = i;
    }
}
