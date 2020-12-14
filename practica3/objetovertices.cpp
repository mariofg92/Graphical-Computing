#include "objetovertices.h"

objetoVertices::objetoVertices(vector <float> &flotantes){
    introducirVertices(flotantes);
}


void objetoVertices::draw_vertices(){
    glColor3f(0,0,0);
    glPointSize(4);

    glBegin(GL_POINTS);

    for(unsigned int i=0; i<vertices.size();i++){
        glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
    }
    glEnd();
}

void objetoVertices::introducirVertices(vector<float> &flotantes){
    vertices.resize(flotantes.size()/3);

    for(unsigned int i=0; i<vertices.size(); i++){
        vertices[i].x=flotantes[i*3];
        vertices[i].y=flotantes[i*3+1];
        vertices[i].z=flotantes[i*3+2];
    }
}

void objetoVertices::introducirVertices(vector<_vertex3f> &vert){
    vertices = vert;
}

_vertex3f objetoVertices::get(unsigned int i){
    return vertices[i];
}

int objetoVertices::numeroVertices(){
    return vertices.size();
}

vector<_vertex3f> objetoVertices::getVector(){
    return vertices;
}
