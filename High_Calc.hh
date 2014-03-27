#ifndef _HIGH_CALC
#define _HIGH_CALC

#include <vector>
#include <GL/glut.h>
#include <math.h>

class High_Calc {

public:
    
    High_Calc ( std::vector < int > , double , double, double);

    void genere_point();
    void genere_vertex();
    

    double get_high(const double & , const double &)const;

    void genere_Normal();
    void Vecteur_Unite(float _norm[], int);

    void display();

    int * get_vertex();
    float * get_point();
    float * get_color();
    int get_w() const;
    double get_zoom_z()const;
    double get_zoom_x() const;

    int get_size();
    
private:
    double m_zoom_x, m_zoom_z, m_zoom_y;
    std::vector < int > height;
    float * point;
    float * color;
    float * norm;
    int size;
    int * vert;
    int W;
};




#endif
