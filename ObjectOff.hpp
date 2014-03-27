#ifndef _OBJECT_OFF
#define _OBJECT_OFF

#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <vector>
#include <math.h>

/* Classe permettant de charger un objet depuis un fichier .off et de l'afficher */

class ObjectOff {
public:
    ObjectOff(const char *);
    ObjectOff(const std::string);
    ObjectOff(std::vector<float>&, std::vector<int>&);
    void display();
    void set_pos(const double &x, const double &y, const double &z);

    void Vecteur_Unite(float norm[3]);
    void Normal();
    
private:
    void load(const char *);

    int nbSommets;
    int nbIndex;
    float *sommets;
    GLuint *myindex;
    float * norm;

    double m_x, m_y, m_z;
};

#endif
