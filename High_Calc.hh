#ifndef _HIGH_CALC
#define _HIGH_CALC

#include <vector>
#include <math.h>

class High_Calc {

public:
    
    High_Calc ( std::vector < int > );

    void genere_point();
    void genere_vertex();
    

    double get_high(const double & , const double &)const;

    int * get_vertex();
    float * get_point();
    float * get_color();
    int get_w();

    int get_size();
    
private:
    
    std::vector < int > height;
    float * point;
    float * color;
    int size;
    int * vert;
    int W;
};




#endif
