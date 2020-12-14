#ifndef OBJETOVERTICES_H
#define OBJETOVERTICES_H

#include"vertex.h"
#include <GL/gl.h>

#include<vector>

class objetoVertices
{

private:
        vector<_vertex3f > vertices;

public:


    objetoVertices(vector <float> &flotantes);
    objetoVertices(){}

    void draw_vertices();
    void introducirVertices(vector<float> &flotantes);
    void introducirVertices(vector<_vertex3f> &vertx);
    _vertex3f get(unsigned int i);
    int numeroVertices();
    vector<_vertex3f> getVector();

};

#endif 
