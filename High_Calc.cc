#include "High_Calc.hh"
#include <iostream>
using namespace std;

High_Calc::High_Calc ( vector <int> v , double zoom_x, double zoom_z, double zoom_y) {
    W = sqrt(v.size());
    vert = new int[W * 2 * W];
    point = new float[W * W * 3];
    color = new float[W * W * 3];
    norm = new float[W * W * 3];

    m_zoom_x = zoom_x;
    m_zoom_z = zoom_z;
    m_zoom_y = zoom_y;
    for ( auto it : v ) {
	height.push_back ( (it - 128) * zoom_y);
    }
    genere_point();
    genere_vertex();
    genere_Normal();
}


void High_Calc::genere_point ( ) {
    int c = 0;
    int d = 0;
    cout << m_zoom_y << endl;
    for ( int j = 0 ; j < W ; j++ ) {
	for ( int i = 0 ; i < W ; i ++ ) {
	    int a = rand()%5/10.0;
	    if ( height[i + j * W] >= (90 * m_zoom_y)) {
		color[d] = 1 - a;
		color[d+1] = 1 - a;
		color[d+2] = 1 - a;
	    } else if ( height[i + j * W] >= (30*m_zoom_y)) {
		color[d] = 24/255.0 + a;
		color[d+1] = 99/255.0 + a;
		color[d+2] = 5/255.0 + a;
	    } else if ( height[i + j * W] >= (10*m_zoom_y) ) {
		color[d] = 99/255.0 + a;
		color[d+1] = 60/255.0 + a;
		color[d+2] = 5/255.0 + a;
	    } else if ( height[i + j * W] >= (-10 * m_zoom_y) ) {
		color[d] = 234/255.0 + a;
		color[d+1] = 211/255.0 + a;
		color[d+2] = 82/255.0 + a;
	    } else {
		color[d] = 112/255.0 + a;
		color[d+1] = 111/255.0 + a;
		color[d+2] = 108/255.0 + a;
	    }
	    
	    point [ c ] = j * m_zoom_x;
	    point [ c + 2 ] = i * m_zoom_z;
	    point [ c + 1 ] = height[i + j * W];
	    c += 3;
	    d+= 3;
	}
    }
}


int High_Calc::get_w() const{
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



void High_Calc::Vecteur_Unite(float _norm[], int nb) {
    float length;
    length = (float)sqrt((_norm[nb] * _norm[nb]) + (_norm[nb+1] * _norm[nb+1]) + (_norm[nb+2]*_norm[nb+2]));
    if ( length == 0.0f ) {
	length = 1.0f;
    }
    _norm[nb] /= length;
    _norm[nb+1] /= length;
    _norm[nb+2] /= length;	   
}
 

void High_Calc::genere_Normal() {
    int x = 0, y =  1, z =  2;
    cout << W * W << endl;
    for ( int j = 0 ; j < W  ; j++) {
	int f = j * W * 3;
	for ( int i = 0 ; i < W * 3 ; i+=3 ) {
	    float v1[3], v2[3];
	    v1[x] = point[i + f] - point[i + 3 + f];
	    v1[y] = point[i + 1 + f] - point[ i + 1 + 3 + f];
	    v1[z] = point[i + 2 + f] - point[i + 2 + 3 + f];
	    v2[x] = point[i + 3 + f] - point[i + 6 + f];
	    v2[y] = point[i + 3 + 1 + f] - point[i + 6 + 1 + f];
	    v2[z] = point[i + 3 + 2 + f] - point[i + 6 + 2 + f];
	    norm[i + f] = (v1[y] * v2[z] - v1[z]*v2[y]);
	    norm[i+1 + f] = (v1[z] * v2[x] - v1[x]*v2[z]);
	    norm[i+2 + f] = (v1[x]*v2[y] - v1[y]*v2[x]);
	    Vecteur_Unite(norm, i*W + f);
	}
    }
}



double  High_Calc::get_high(const double  & x, const double & z) const{
    double x_ = x / m_zoom_x;
    double z_ = z / m_zoom_z;
    return (double)height[(int)x_ * W + (int)z_];
}

int * High_Calc::get_vertex ( ) {
    return vert;
}


float * High_Calc::get_point ( ) {
    return point;
}

float * High_Calc::get_color() {
    return color;
}


int High_Calc::get_size ( ) {
    return size;
}



double High_Calc::get_zoom_z() const {
    return m_zoom_z;
}

double High_Calc::get_zoom_x() const {
    return m_zoom_x;
}


void High_Calc::display() {

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, color);
    glNormalPointer(GL_FLOAT,0, norm);
    glVertexPointer ( 3, GL_FLOAT, 0, point );
    for ( int i = 0 ; i < W - 1 ; i++) {
	glDrawElements( GL_TRIANGLE_STRIP , W*2 , GL_UNSIGNED_INT, &vert[W * 2 * i]);
	
    }    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

}
