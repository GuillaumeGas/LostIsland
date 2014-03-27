#include "Cube.hpp"




Cube::Cube(double x,double y,double z, double h, double l, double L):m_x(x), m_y(y), m_h(h), m_l(l), m_L(L), m_z(z){



    point[0] = x; point[1] = y; point[2] = z;

    point[3] = x + l; point[4] = y; point[5] = z;

    point[6] = x + l; point[7] = y + h; point[8] = z;

    point[9] = x; point[10] = y + h; point[11] = z;

    point[12] = x; point[13] = y; point[14] = z + L;

    point[15] = x + l; point[16] = y; point[17] = z + L;

    point[18] = x + l ; point[19] = y + h; point[20] = z + L;

    point[21] = x; point[22] = y + h; point[23] = z + L;

    devant[0] = 0; devant[1] = 1; devant[2] = 2; devant[3] = 3;

    derriere[0] = 4; derriere[1] = 5; derriere[2] = 6; derriere[3] = 7;

    droite[0] = 1; droite[1] = 5; droite[2] = 6; droite[3] = 2; 
 
    gauche[0] = 0; gauche[1] = 4; gauche[2] = 7; gauche[3] = 3;

    haut[0] = 0; haut[1] = 1; haut[2] = 5; haut[3] = 4;

    bas[0] = 2; bas[1] = 3; bas[2] = 7; bas[3] = 6;

    count[0] = 5;
    count[1] = 4;
    Normal();
}

							  
void Cube::display(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glColor4d(0,0.2,0.8, 0.2);
    glVertexPointer(3,GL_FLOAT,0,point);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, devant);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, derriere);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, droite);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, gauche);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, haut);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bas);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_BLEND);
}		      

void Cube::display(const double r, const double g, const double b, const double alpha){
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glColor4d(r,g,b,alpha);
    glVertexPointer(3,GL_FLOAT,0,point);
    glNormalPointer(GL_FLOAT, 0, norm);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, devant);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, derriere);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, droite);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, gauche);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, haut);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bas);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisable(GL_BLEND);
}		      



void Cube::Vecteur_Unite(float norm[3]) {
    float length;
    length = (float)sqrt((norm[0] * norm[0]) + (norm[1] * norm[1]) + (norm[2]*norm[2]));
    if ( length == 0.0f ) {
	length = 1.0f;
    }
    norm[0] /= length;
    norm[1] /= length;
    norm[2] /= length;	   
}
 

void Cube::Normal() {
    int x = 0, y = 1, z = 2;
    for (int i = 0 ; i < 24 ; i+=3) {
	
	float v1[3], v2[3];
	v1[x] = point[i] - point[i + 3];
	v1[y] = point[i + 1] - point[ i + 1 + 3];
	v1[z] = point[i+2] - point[i + 2 + 3];
	v2[x] = point[i + 3] - point[i + 6];
	v2[y] = point[i + 3 + 1] - point[i + 6 + 1];
	v2[z] = point[i + 3 + 2] - point[i + 6 + 2];
	norm[i] = (v1[y] * v2[z] - v1[z]*v2[y]);
	norm[i+1] = (v1[z] * v2[x] - v1[x]*v2[z]);
	norm[i+2] = (v1[x]*v2[y] - v1[y]*v2[x]);
	Vecteur_Unite(norm);
    }
}


double Cube::_y() const {
    return m_y + m_h;
}
