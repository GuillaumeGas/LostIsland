#ifndef _HIGH_CALC
#define _HIGH_CALC

#include <vector>
#include <math.h>

class High_Calc {

public:
    
    High_Calc ( std::vector < int > );

    void genere_point();
    void genere_vertex();
    

    int * get_vertex();
    float * get_point();

    int get_w();

    int get_size();
    
private:
    
    std::vector < int > height;
    float * point;
    int size;
    int * vert;
    int W;
};




#endif
