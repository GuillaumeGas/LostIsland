#ifndef _TREE
#define _TREE

#include <vector>
#include "Cube.hpp"

class Tree {
public:
    Tree(double x, double y, double z, double h, double l, double L, double zoom_x, double zoom_y, double zoom_z);
    void display();

private:
    Cube tronc;
    std::vector<Cube> branches;
    std::vector<Cube> leaves;
};

#endif
