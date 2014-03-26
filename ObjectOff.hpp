#ifndef _OBJECT_OFF
#define _OBJECT_OFF

#include <iostream>
#include <fstream>
#include <GL/glut.h>

/* Classe permettant de charger un objet depuis un fichier .off et de l'afficher */

class ObjectOff {
public:
    ObjectOff(const char *);
    ObjectOff(const std::string);

    void display();
    void set_pos(const double x, const double y, const double z);

private:
    void load(const char *);

    int nbSommets;
    int nbIndex;
    float *sommets;
    GLuint *myindex;

    double m_x, m_y, m_z;
};

#endif
