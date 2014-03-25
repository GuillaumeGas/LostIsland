#ifndef _TREE
#define _TREE

#include <vector>
#include "Branch.hpp"

class Tree {
public:
    Tree(double x, double y, double z, double h, double l, double L, double zoom_x, double zoom_y, double zoom_z);
    void display();

private:
    Branch tronc;
    std::vector<Branch> branches;
};

#endif
