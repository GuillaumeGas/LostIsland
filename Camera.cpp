#include "Camera.hpp"
#include <GL/glu.h>
#include <math.h>
#include <iostream>

Camera::Camera() {
  m_eyeX = 3;
  m_eyeY = m_eyeZ = 4;

  m_centerX = m_centerY = m_centerZ = 0;
  m_upX = m_upY = 0;
  m_upZ = 1;
  m_vitesse = 0.1;
  m_posx = 0;
  m_posy = 0;
  m_phi = 0.0;
  m_theta = 0.0;
  fly = false;
}

void Camera::look() {
  gluLookAt(m_position.X, m_position.Y, m_position.Z, m_target.X, m_target.Y, m_target.Z, m_upX, m_upY, m_upZ);
}

void Camera::setLook(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ) {
    m_position.X =eyeX;
    m_position.Y = eyeY;
    m_position.Z = eyeZ;
    m_target.X = centerX;
    m_target.Y = centerY;
    m_target.Z = centerZ;
    
  m_eyeX = eyeX;
  m_eyeY = eyeY;
  m_eyeZ = eyeZ;
  m_centerX = centerX;
  m_centerY = centerY;
  m_centerZ = centerZ;
  m_upX = upX;
  m_upY = upY;
  m_upZ = upZ;
}

//void Camera::setLookAt(double x, double y, double z) {
void Camera::setLookAt(position_t pos, int &i) {
    if(i > 2){
	m_theta -= (1000/2-pos.m_x) * m_vitesse;
	m_posx = pos.m_x;


	m_phi -= (pos.m_y- 768/2)*m_vitesse;
	m_posy = pos.m_y;

	if(m_phi > 89)
	    m_phi = 89;
	if (m_phi < -89)
	    m_phi = -89;
		
	static const Vector3D up(0,0,1);
	double r_temp = cos(m_phi * M_PI/180);
	m_forward.Y = sin(m_phi * M_PI/180) ;

	m_forward.Z = r_temp*cos(m_theta*M_PI/180);
	m_forward.X = r_temp*sin(-m_theta*M_PI/180);
	
	m_left = up.crossProduct(m_forward);
	m_left.normalize();
	m_target = m_forward + m_position;
   }
}


void Camera::calc_high(const High_Calc & h, const Cube & c ) {
    m_position._Y() = h.get_high(m_position._X(), m_position._Z()) + 5.0;
    if ( m_position._Y() <= c._y() ) {
	m_position._Y() = c._y() + 1;
    }
}


    void Camera::MovePosition(Event e, const High_Calc & h, const Cube &c){
    double realspeed = 50;
    if ( e[SHIFT] ) realspeed *= 2;
    if ( !e[SPACE] ) {
	realspeed = 0.5;
	if ( e[SHIFT] ) realspeed *= 2;
	calc_high(h, c);
	if (m_position._X() < 0 ) {
	    m_position._X() = 0;
	} else if ( m_position._X() >= h.get_w() * h.get_zoom_x()) {
	    m_position._X() = h.get_w() * h.get_zoom_x();
	}
	if ( m_position._Z() < 0) {
	    m_position._Z() = 0;
	} else if ( m_position._Z() >= h.get_w() * h.get_zoom_z() ) {
	    m_position._Z() = h.get_w() * h.get_zoom_z();
	}
    }
    if(e[UP]) {
	m_position += m_forward * realspeed;
    }
    if(e[DOWN]) {
	m_position -= m_forward * realspeed;
    }
    m_target = m_position + m_forward;
}


Vector3D & Camera::position() {
    return m_position;
}


Vector3D  Camera::target() {
    return m_target;
}
