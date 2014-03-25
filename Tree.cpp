#include "Tree.hpp"

using namespace std;

Tree::Tree(double x, double y, double z, double h, double l, double L, double zoom_x, double zoom_y, double zoom_z) : tronc(x*zoom_x, y*zoom_y, z*zoom_z, h*zoom_y, l*zoom_z, L*zoom_x) {
    branches.push_back(Branch(x*zoom_x, (y+60)*zoom_y, z*zoom_z, 5*zoom_y, 2*zoom_z, 0.3*zoom_x));
    branches.push_back(Branch((x-2)*zoom_x, (y+80)*zoom_y, z*zoom_z, 5*zoom_y, 2*zoom_z, 0.3*zoom_x));
    branches.push_back(Branch(x*zoom_x, (y+70)*zoom_y, z*zoom_z, 2*zoom_y, 0.3*zoom_z, 2*zoom_x));
    branches.push_back(Branch(x*zoom_x, (y+50)*zoom_y, (z-2)*zoom_z, 2*zoom_y, 0.3*zoom_z, 2*zoom_x));
}

void Tree::display() {
    tronc.display();
    for(auto it : branches) {
	it.display();
    }
}
