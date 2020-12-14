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
#include <cmath>

using namespace std;


struct Figura{

vector<float> vertices;
vector<int> caras;

};

void draw_cube();

void draw_vertices(vector<float> &Vertices);

void draw_mode(vector<float> &Vertices, vector<int> &Caras, int mode);

void DibujarPly(char *File_name, int mode);

void GeneraSemicirculo(float radio, int n_vertices, vector<float> &Vertices, vector<int> &Caras);

void PintaSemicirculo(float radio, int n_vertices);

void GenerarPorRevolucion(Figura &nueva, int divisiones, int d_mode);

void PintaEsfera(float radio, int n_vertices);





