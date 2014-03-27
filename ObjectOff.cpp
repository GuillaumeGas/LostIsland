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
    norm = new float[somm.size()];
    Normal();
}




void ObjectOff::load(const char * file) {
    ifstream f(file, ios::in);
    string ch;
    int aux;

    f >> ch >> nbSommets >> nbIndex >> aux;

    if(ch == "OFF") {
	sommets = new float[nbSommets*3];
	norm = new float[nbSommets * 3];
	int j = 0;
	for(int i = 0; i < nbSommets; i++) {
	    f >> sommets[j++] >> sommets[j++] >> sommets[j++];
	}
	Normal();

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
    glEnableClientState(GL_NORMAL_ARRAY);
    //    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //glTexCoordPointer(3, GL_FLOAT, 0, sommets);
    glNormalPointer(GL_FLOAT, 0, norm);
    glVertexPointer(3, GL_FLOAT, 0, sommets);
    glDrawElements(GL_TRIANGLES, nbIndex*3, GL_UNSIGNED_INT, myindex);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();
}

void ObjectOff::set_pos(const double &x, const double &y, const double &z) {

    m_x = x;
    m_y = y;
    m_z = z;
}




void ObjectOff::Vecteur_Unite(float norm[3]) {
    float length;
    length = (float)sqrt((norm[0] * norm[0]) + (norm[1] * norm[1]) + (norm[2]*norm[2]));
    if ( length == 0.0f ) {
	length = 1.0f;
    }
    norm[0] /= length;
    norm[1] /= length;
    norm[2] /= length;	   
}
 

void ObjectOff::Normal() {
    int x = 0, y = 1, z = 2;
    for (int i = 0 ; i < nbSommets*3 ; i+=3) {
	
	float v1[3], v2[3];
	v1[x] = sommets[i] - sommets[i + 3];
	v1[y] = sommets[i + 1] - sommets[ i + 1 + 3];
	v1[z] = sommets[i+2] - sommets[i + 2 + 3];
	v2[x] = sommets[i + 3] - sommets[i + 6];
	v2[y] = sommets[i + 3 + 1] - sommets[i + 6 + 1];
	v2[z] = sommets[i + 3 + 2] - sommets[i + 6 + 2];
	norm[i] = (v1[y] * v2[z] - v1[z]*v2[y]);
	norm[i+1] = (v1[z] * v2[x] - v1[x]*v2[z]);
	norm[i+2] = (v1[x]*v2[y] - v1[y]*v2[x]);
	Vecteur_Unite(norm);
    }
}
