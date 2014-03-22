#ifndef _CAMERA
#define _CAMERA

/**
   Classe représentant une caméra pouvant se déplacer 
   à une certaines vitesse, etc...
*/

#include "Event.hpp"
#include "High_Calc.hh"
#include "Vector3d.h"
#include "Cube.hpp"

class Camera {

public:
    Camera();
    //Camera(double eye_x, double eye_y, double eye_z, double center_x, double center_y, double center_z, double up_x, double up_y, double up_z); 

    void look();
    //void setLookAt(double x, double y, double z);
    void setLookAt(position_t pos, int &);
    void setLook(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ);
    void MovePosition(Event e, const High_Calc & h, const Cube & c);

    Vector3D & position();

private:

    void calc_high(const High_Calc & h, const Cube & );


    double m_eyeX, m_eyeY, m_eyeZ;
    double m_centerX, m_centerY, m_centerZ;
    double m_upX, m_upY, m_upZ;

    double m_theta; //horiz
    double m_phi;  //verti

    double m_vitesse;
    
    double m_posx, m_posy;

    Vector3D m_position;
    Vector3D m_target;
    Vector3D m_forward;
    Vector3D m_left;
    bool fly;
};

#endif
