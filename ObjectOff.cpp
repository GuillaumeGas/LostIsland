#include "ObjectOff.hpp"

using namespace std;

ObjectOff::ObjectOff(const char * file) {
    nbSommets = 0;
    nbIndex   = 0;
    sommets   = NULL;
    myindex   = NULL;
    m_x = m_y = m_z = 100;

    load(file);
}
ObjectOff::ObjectOff(const string file) {
    nbSommets = 0;
    nbIndex   = 0;
    sommets   = NULL;
    myindex   = NULL;
    m_x = m_y = m_z = 100;

    load(file.c_str());
}


ObjectOff::ObjectOff(vector<float> &somm, vector<int> &index) {
    myindex = new GLuint[index.size()];
    for ( int i = 0 ; i < index.size() ; i++ ) {
	myindex[i] = index[i];
    }
    sommets = new float[somm.size()];
    for ( int i = 0 ; i < somm.size() ; i++ ) {
	sommets[i] = somm[i];
    }
}




void ObjectOff::load(const char * file) {
    ifstream f(file, ios::in);
    string ch;
    int aux;

    f >> ch >> nbSommets >> nbIndex >> aux;

    if(ch == "OFF") {
	sommets = new float[nbSommets*3];
	int j = 0;
	for(int i = 0; i < nbSommets; i++) {
	    f >> sommets[j++] >> sommets[j++] >> sommets[j++];
	}
	
	int nb;
	f >> nb;
	myindex = new GLuint[nbIndex*nb];
	j = 0;
	for(int i = 0; i < nbIndex; i++) {
	    for(int k = 0; k < nb; k++) {
		f >> myindex[j++];
	    }
	    f >> nb;
	}
    } else {
	cout << "Erreur, fichier inconnu." << endl;
	throw -1;
    }
    f.close();
}



void ObjectOff::display() {

    glPushMatrix();
    glTranslated(m_x, m_y, m_z);

    glEnableClientState(GL_VERTEX_ARRAY);
    //    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //glTexCoordPointer(3, GL_FLOAT, 0, sommets);
    glVertexPointer(3, GL_FLOAT, 0, sommets);
    glDrawElements(GL_TRIANGLES, nbIndex*3, GL_UNSIGNED_INT, myindex);
    glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();
}

void ObjectOff::set_pos(const double &x, const double &y, const double &z) {

    m_x = x;
    m_y = y;
    m_z = z;
}
