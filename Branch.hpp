#ifndef _BRANCH
#define _BRANCH

#include <iostream>
#include <GL/glut.h>
#include <math.h>

class Branch  {
public:
    Branch(double x, double y, double z, double h, double l, double L);    
    void display();

private:
    double m_x ,m_y, m_z, m_h, m_l, m_L;
    GLfloat point[24];
    GLsizei count[6];
    GLubyte devant[4], derriere[4],
	droite[4], gauche[4], haut[4], bas[4];
    GLvoid *cube[4];
    

};

#endif
