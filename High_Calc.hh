#ifndef _HIGH_CALC
#define _HIGH_CALC

#include <vector>

class High_Calc {

public:
    
    High_Calc ( std::vector < std::vector < int > > );

    void genere_point();
    void genere_vertex();
    

    int * get_vertex();
    float * get_point();

    int get_size();
    
private:
    
    std::vector < std::vector < int > > height;
    float * point;
    int size;
    int * vert;
};




#endif
