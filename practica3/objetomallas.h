#ifndef objetoMallas_H
#define objetoMallas_H

#include "objetovertices.h"

class objetoMallas
{

private:

    objetoVertices objetoVert;
    vector<_vertex3ui>caras;

    vector<_vertex3f> normalesCaras;
    vector<_vertex3f> normalesVertices;

public:


    objetoMallas(){};
    objetoMallas(objetoVertices &objVert, vector<int> & car);
    objetoMallas(vector<float> &vertices, vector<int> & car);


    void insertarCaras(vector<int> & car);
    void insertarVertices(vector<float> & ver);
    void draw_vertices();
    void draw_aristas();
    void draw_caras(float a,float b, float c);
    void draw_ajedrez();
    void modeladorotacion(int lados);
    void insertarVertices(vector<_vertex3f> & verti);
    void introducirCaras(vector<_vertex3ui> & car);
};




#endif // objetoMallas_H
