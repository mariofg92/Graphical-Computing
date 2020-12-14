//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "file_ply_stl.h"

using namespace std;


struct Figura{

vector<float> vertices;
vector<int> caras;

};

void draw_cube();

void draw_vertices(vector<float> &Vertices);

void draw_mode(vector<float> &Vertices, vector<int> &Caras, int mode);






